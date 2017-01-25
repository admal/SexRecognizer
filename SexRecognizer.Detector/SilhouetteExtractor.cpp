#include "SilhouetteExtractor.h"
#include "ImageResizer.h"

using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace Common;
using namespace Extract;



SilhouetteExtractor::SilhouetteExtractor(){
	//CPU
	//this->hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	//GPU
	Size win_size = Size(48, 96);
	Size block_size = Size(16, 16);
	Size block_stride = Size(8, 8);
	Size cell_size = Size(8, 8);
	int nbins = 9; //only 9 is supported for now
	this->gpu_hog = cv::cuda::HOG::create(win_size, block_size, block_stride, cell_size, nbins);
	//cv::Mat detector = this->gpu_hog->getDefaultPeopleDetector();
	this->gpu_hog->setSVMDetector(this->gpu_hog->getDefaultPeopleDetector());
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
	const int FRAME_WIDTH = 40;
	cv::Mat display2img;
	//CPU
	////HOGDescriptor hog;
	////hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	int minOffset = 0, maxOffset = 40;
	double meanShift = 0;
	int shiftCounter = 0;
	Rect prevRect;
	int imgWidth = frames[0].cols, imgHeight = frames[0].rows, imgScale = frames[0].cols/80;
	bool firstDetected = false; // states that iteration is the first in which the person was detected
	bool outOfBounds = false;  // when the person can't be put in the middle of 60x60 frame it's out of image
	int estimatedPosCount = 0; // when algorithm fails to detect a person but it should be still in an image it works as a boundary estimation counter
	int estimatedPosMax = 3; // upper bound for guessed position
	int prevRecalcOffset;
	int pixelThreshold = 0;
	for (int x = 0; x < frames.size(); x++){
		if (outOfBounds){ // if OOB put all -1 to the end
			for (int i = v.size(); i < frames.size(); i++)
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
			if (i == found.size() - 1) // when all rectangles compared the biggest is the only one left
				found_filtered.push_back(max);
		}
		if (found.size() == 0 && firstDetected) // if no person found but it was detected previously we estimate the position and calc if it's still in frame
		{
			estimatedPosCount++; // increment estimated positions used count
			max = prevRect;
			max.x += std::round(meanShift);
			if (meanShift > 0 && (max.x + max.width) < imgWidth){ // if moving right
				found_filtered.push_back(max);
			}
			else if (meanShift < 0 && (max.x) > minOffset) // if moving left
			{
				found_filtered.push_back(max);
			} else
			{
				outOfBounds = true;
			}
			if (estimatedPosCount >= estimatedPosMax) //we limit number of estimations between caught frames
			{
				outOfBounds = true;;
			}
		}
		if (found.size() == 0 && !firstDetected)
		{
			v.push_back(-1);
		}
		
		for (i = 0; i < found_filtered.size(); i++)  // TODO: 'improvement' found_filtered should always have 1 member so can be reduced to single var
		{

			//CALCULATING SILHOUETTE FRAME OFFSET
			// resizing to 80 x 60 and recalculating the x offset
			int offset = found_filtered[0].x / imgScale;
			int recalculatedOffeset = offset - ((FRAME_WIDTH - (found_filtered[0].width / imgScale)) / 2);
			
			if (!firstDetected) // init meanShift , determine the direction the person is walking
			{
				if (recalculatedOffeset >= maxOffset)
				{
					meanShift = -0.01;
				}
				else if (recalculatedOffeset <= minOffset){
					meanShift = 0.01;
				}
			}
			else // calculates mean shift needs to find a person at least once before, it ignores the value if it points in wrong direction
			{
				// MEAN SHIFT
				double newMeanShift = (double)((meanShift + calcShift(prevRecalcOffset, recalculatedOffeset)) / (double)shiftCounter);
				if ((meanShift < 0 && newMeanShift < 0) || (meanShift > 0 && newMeanShift > 0)){
					meanShift = newMeanShift;
					estimatedPosCount = 0;
				}
			}

			if (firstDetected){ // CHECK OUTLIERS (HOG DETECTION ERRORS) and person OOB - for example when instead of a walking person it locks on a fire extinguisher
				if (meanShift < 0 && prevRecalcOffset < recalculatedOffeset ) // if moving left and the frame suggests the next step is to right ignore it and calc from mean shift
				{
					// Take the previous offset and add a meanShift
					recalculatedOffeset = prevRecalcOffset + std::round(meanShift);
				}
				if (meanShift > 0 && prevRecalcOffset > recalculatedOffeset) // similiar but the other way around
				{
					recalculatedOffeset = prevRecalcOffset + std::round(meanShift);
				}
				
			}
			
			if (recalculatedOffeset < (minOffset - pixelThreshold) && meanShift < 0) { //if moving left gets OOB
				outOfBounds = true; // if the frame was calculated to be outside of image for the person to be in the middle we stop the detection
				break;
			}
			else if (recalculatedOffeset >(maxOffset + pixelThreshold) && meanShift > 0){ // if moving right gets OOB
				outOfBounds = true;
				break;
			}
			else // here we check if a person can be put in the middle of a 60x60 frame
			{
				prevRecalcOffset = recalculatedOffeset; // save calculated offset for counting shift
				if (recalculatedOffeset < 0 && recalculatedOffeset >= (minOffset - pixelThreshold))
				{
					recalculatedOffeset = 0;
				}
				if (recalculatedOffeset > maxOffset && recalculatedOffeset <= (maxOffset + pixelThreshold))
				{
					recalculatedOffeset = maxOffset;
				}
				
				if (recalculatedOffeset < 0 || recalculatedOffeset > maxOffset)
				{
					recalculatedOffeset = -1; // which states that an offset for a frame is not yet usable
				}
			}

			firstDetected = true;
			prevRect = max;
			
			v.push_back(recalculatedOffeset);
			//DRAWING 
			Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.06);
			r.height = cvRound(r.height*0.9);
			display2img = cv::Mat(this->resizedFrames[x]);
			rectangle(frames[x], r.tl(), r.br(), cv::Scalar(0, 255, 0), 2); //draw best rectangle
			Rect r2 = found_filtered[i];
			r2.x = recalculatedOffeset;
			r2.width = 40;
			r2.y = 0;
			r2.height = 80;
			if (recalculatedOffeset != -1)
				rectangle(display2img, r2.tl(), r2.br(), cv::Scalar(0, 0, 255), 2); //draw silhouette frame
		}
		
		if (firstDetected)
		{
			shiftCounter++;
		}
		cv::namedWindow("display", 1);
		cv::imshow("display", frames[x]);
		cv::namedWindow("display2", 1);
		cv::imshow("display2", display2img);
		cv::waitKey(1);
	}
	if (v.size() < frames.size()) // This shouldn't happen it's just for safety if something fails
	{
		for (int x = v.size() - 1; x < frames.size(); x++){
			v.push_back(-1);
		}
	}
	return v;
}

/*
 * One Person movie can be extracted at one time
 */
std::vector<int> SilhouetteExtractor::extract(std::vector<cv::Mat> frames) {
	//subtractedFrames = this->subtractor->subtract(frames);
	Extract::ImageResizer resizer(160, 120);  // resize frames to better extract silhouette offset
	std::vector<cv::Mat> resizedFramesForHOG = resizer.resizeFrames(frames);
	resizer.setSize(Size(80, 60));  // resize frames to final 80 x 60 res
	this->resizedFrames = resizer.resizeFrames(frames);
	std::vector<int> xSilhouetteOffsets = SilhouetteExtractor::findSilhouetteOffset(resizedFramesForHOG); // find a slhouette
	return xSilhouetteOffsets;
}

std::vector<cv::Mat> SilhouetteExtractor::getResizedFrames()
{
	return this->resizedFrames;
}

