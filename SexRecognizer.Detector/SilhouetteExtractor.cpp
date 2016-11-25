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
}

/*
 * Calculates the shift in X-axis between two frames.
 * return val > 0  means it's moving right ; val < 0 it's moving left;
 */
double calcShift(Rect a, Rect b) 
{	
	return b.x - a.x;;
}

/*
 * Calculates silhouette frame (60 x 60) offset value -1 in a vector where the silhouette is not detected
 * This method should be run for 1 set of images of 1 walk
 */
std::vector<int> SilhouetteExtractor::findSilhouetteOffset(std::vector<cv::Mat> frames){
//	imwrite("a.png", frames[10]);
//	imwrite("b.png", frames[30]);
//
//	int edgeThresh = 1;
//	int lowThreshold = 64;
//	int const max_lowThreshold = 100;
//	int ratio = 3;
//	int kernel_size = 3;
//	std::vector<int> v;
//
//
//	//edge detection on images and find left and right maximas then center the frame and calculate the offset
//	for (int i = 0; i < frames.size(); i++)
//	{
//		Mat dst;
//		dst.create(frames[0].size(), frames[0].type());
//		//cuda::cvtColor(cv::InputArray(frames[i]), src_gray, CV_BGR2GRAY);
//		Mat detectedEdges;
//		blur(frames[i], detectedEdges, Size(3, 3));
//		imwrite("c.png", detectedEdges);
//		Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold*ratio, kernel_size);
//		dst = Scalar::all(0);
//		frames[i].copyTo(dst, detectedEdges);
//		imwrite("s" + to_string(i) + ".png", dst);
//	}
	std::vector<int> v;
	Size win_size = Size(64, 128);
	Size block_size = Size(16, 16);
	Size block_stride = Size(8, 8);
	Size cell_size = Size(8, 8);
	int nbins = 9; //only 9 is supported for now
	//CPU
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	// TODO: GPU implementation
	cv::Ptr<cv::cuda::HOG> gpu_hog = cv::cuda::HOG::create(win_size, block_size, block_stride, cell_size, nbins);
	Mat detector = gpu_hog->getDefaultPeopleDetector();
	gpu_hog->setSVMDetector(detector);
	gpu_hog->setScaleFactor(1.05);
	double meanShift = 0;
	int shiftCounter = 0;
	Rect prevRect;
	int imgWidth = frames[0].cols, imgHeight = frames[0].rows, imgScale = frames[0].cols/80;
	bool firstDetected = false; // states that iteration is the first in which the peson was detected

	for (int x = 0; x < frames.size(); x++){
		cuda::GpuMat gpu_img;
		vector<Rect> found, found_filtered;
		// GPU
//		gpu_img.upload(frames[x]);
//		gpu_hog->detectMultiScale(frames[x], found);
		// CPU
		hog.detectMultiScale(frames[x], found, 0, Size(4, 4), Size(8, 8), 1.5, 0);
		
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
			max.x += meanShift;
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
			recalculatedOffeset = (recalculatedOffeset > 0) ? recalculatedOffeset : 0;
			recalculatedOffeset = (recalculatedOffeset + 60 < 80) ? recalculatedOffeset : 20;
			v.push_back(recalculatedOffeset);

			Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.06);
			r.height = cvRound(r.height*0.9);
			rectangle(frames[x], r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);

		}

		if (found.size() != 0)
		{
			if (firstDetected) // this will be entered when a second time person is detected
			{
				meanShift = (meanShift + calcShift(prevRect, max)) / shiftCounter;
			}
			prevRect = max;	
			firstDetected = true;
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
	Extract::ImageResizer resizer(320, 240);  // resize frames to better extract silhouette offset
	std::vector<cv::Mat> resizedFrames = resizer.resizeFrames(frames);
	std::vector<int> xSilhouetteOffsets = SilhouetteExtractor::findSilhouetteOffset(resizedFrames); // find a slhouette
	resizer.setSize(Size(80, 60));  // resize frames to final 80 x 60 res
	resizedFrames = resizer.resizeFrames(frames);
	return xSilhouetteOffsets;
}

std::vector<cv::Mat> SilhouetteExtractor::getResizedFrames()
{
	return this->resizedFrames;
}

