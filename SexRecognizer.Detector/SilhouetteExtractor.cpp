#include "SilhouetteExtractor.h"
#include "ImageResizer.h"

using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace Common;
using namespace Extract;



SilhouetteExtractor::SilhouetteExtractor(int subtractionType){
	switch (subtractionType){
	case 0:
		this->subtractor = new Extract::BackgroundSubtractorMOG2();
		break;
	default:
		this->subtractor = new Extract::BackgroundSubtractorMOG2();
	}
	//CPU
	this->hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	//GPU
	Size win_size = Size(48, 96);
	Size block_size = Size(16, 16);
	Size block_stride = Size(8, 8);
	Size cell_size = Size(8, 8);
	int nbins = 9; //only 9 is supported for now
	this->gpu_hog = cv::cuda::HOG::create(win_size, block_size, block_stride, cell_size, nbins);
	Mat detector = this->gpu_hog->getDefaultPeopleDetector();
	this->gpu_hog->setSVMDetector(detector);
	this->gpu_hog->setScaleFactor(1.01);
}

/*
 * Calculates the shift in X-axis between two frames.
 * return val > 0  means it's moving right ; val < 0 it's moving left;
 */
double calcShift(int a, int b) 
{	
	return b - a;
}

/*
 * Calculates silhouette frame (60 x 60) offset value -1 in a vector where the silhouette is not detected
 * This method should be run for 1 set of images of 1 walk
 */
std::vector<int> SilhouetteExtractor::findSilhouetteOffset(std::vector<cv::Mat> frames){

	std::vector<int> v;
	
	//CPU
	////HOGDescriptor hog;
	////hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	
	double meanShift = 0;
	int shiftCounter = 0;
	Rect prevRect;
	int imgWidth = frames[0].cols, imgHeight = frames[0].rows, imgScale = frames[0].cols/80;
	bool firstDetected = false; // states that iteration is the first in which the peson was detected
	bool outOfBounds = false;  // when the person can't be put in the middle of 60x60 frame it's out of image
	for (int x = 0; x < frames.size(); x++){
		if (outOfBounds){ // put all -1 to the end
			for (int i = x; i < frames.size(); i++)
			{
				v.push_back(-1);
			}
			break;
		}

		cv::Mat image(frames[x]), imageGray;
		cv::cuda::GpuMat imageGpu;
		cv::cvtColor(image, imageGray, CV_BGR2GRAY);
		imageGpu.upload(imageGray);

		cv::InputArray gpu_img(frames[x]);
		vector<Rect> found, found_filtered;
		// GPU
		this->gpu_hog->detectMultiScale(imageGpu, found);
		// CPU
		//this->hog.detectMultiScale(frames[x], found, 0, Size(4, 4), Size(8, 8), 1.5, 0);
		
		size_t i;	
		
		Rect max(0,0,0,0);

		for (i = 0; i<found.size(); i++) // take the biggest detected rectangle
		{
			Rect r = found[i];
			if (r.area() > max.area())
				max = r;
			if (i == found.size() - 1)
				found_filtered.push_back(max);
		}
		if (found.size() == 0 && firstDetected) // if no person found but it was detected previously we estimate the position and calc if it's still in frame
		{
			max = prevRect;
			max.x += std::round(meanShift);
			if (meanShift > 0){ // if moving right
				if ((max.x + max.width) < imgWidth)
					found_filtered.push_back(max);
			} else if(meanShift < 0) // if moving left
			{
				if ((max.x - max.width) > 0)
					found_filtered.push_back(max);
			} else
			{
				v.push_back(-1);
			}
		}
		if (found.size() == 0 && !firstDetected)
		{
			v.push_back(-1);
		}
		
		for (i = 0; i<found_filtered.size(); i++)  // TODO: found_filtered should always have 1 member so can be reduced to single var
		{

			
			//CALCULATING SILHOUETTE FRAME OFFSET
			// resizing to 80 x 60 and recalculating the x offset
			int offset = found_filtered[0].x / imgScale;
			int recalculatedOffeset = offset - ((60 - (found_filtered[0].width / imgScale)) / 2);

			// CHECK OUTLIERS (HOG DETECTION ERRORS) and person OOB - for example when instead of a walking person it locks on a fire extinguisher
			OUTLIERS_OOB:{
				if (meanShift < 0 && v[v.size() - 1] < recalculatedOffeset) // if moving left and the frame suggests the next step is to right ignore it and calc from mean shift
				{
					// Take the previous offset and add a meanShift
					recalculatedOffeset = v[v.size() - 1] + std::round(meanShift);
				}
				if (meanShift > 0 && v[v.size() - 1] > recalculatedOffeset) // similiar but the other way around
				{
					recalculatedOffeset = v[v.size() - 1] + std::round(meanShift);
				}
				if (recalculatedOffeset < 0 && meanShift < 0) { //if moving left gets OOB
					outOfBounds = true; // if the frame was calculated to be outside of image for the person to be in the middle we stop the detection
					break;
				}
				else if (recalculatedOffeset > 20 && meanShift > 0){ // if moving right gets OOB
					outOfBounds = true;
					break;
				}
				else
				{
					recalculatedOffeset = (recalculatedOffeset >= 0) ? recalculatedOffeset : 0;
					recalculatedOffeset = (recalculatedOffeset + 60 <= 80) ? recalculatedOffeset : 20;
				}
			}
			MEAN_SHIFT:{
				if (firstDetected) // this will be entered when a second time person is detected
				{
					if (recalculatedOffeset == 20)
					{
						meanShift = -0.01;
					} else if(recalculatedOffeset == 0){
						meanShift = 0.01;
					}else{ // the HOG algorithm went crazy or a person was recorded far from the edge
						int change = max.x - prevRect.x;
						if (change != 0) change > 0 ? meanShift = 0.01 : meanShift = -0.01;
					}
					meanShift = (double)((meanShift + calcShift(v[v.size() - 1], recalculatedOffeset)) / (double)shiftCounter);
				}
				prevRect = max;
				firstDetected = true;
			}
			v.push_back(recalculatedOffeset);

			Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.06);
			r.height = cvRound(r.height*0.9);
			rectangle(frames[x], r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
		}

		
		if (firstDetected)
		{
			shiftCounter++;
		}
		namedWindow("a", 1);
		imshow("a", frames[x]);
		waitKey(1);

		//cv::imwrite("a"+to_string(x)+".png", frames[x]);
	}

	return v;
}

/*
 * One Person movie can be extracted at one time
 */
std::vector<int> SilhouetteExtractor::extract(std::vector<cv::Mat> frames) {
	//subtractedFrames = this->subtractor->subtract(frames);
	Extract::ImageResizer resizer(160, 120);  // resize frames to better extract silhouette offset
	std::vector<cv::Mat> resizedFrames = resizer.resizeFrames(frames);
	std::vector<int> xSilhouetteOffsets = SilhouetteExtractor::findSilhouetteOffset(resizedFrames); // find a slhouette
	resizer.setSize(Size(80, 60));  // resize frames to final 80 x 60 res
<<<<<<< HEAD
	resizedFrames = resizer.resizeFrames(resizedFrames);
=======
	this->resizedFrames = resizer.resizeFrames(frames);
>>>>>>> f29a153f9f578529a44cfd9f33e1de2c88d71c9c
	return xSilhouetteOffsets;
}

std::vector<cv::Mat> SilhouetteExtractor::getResizedFrames()
{
	return this->resizedFrames;
}

