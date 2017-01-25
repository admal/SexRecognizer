#pragma once
#include "BackgroundSubtractor.h"


namespace Extract {

	class SilhouetteExtractor {
	private:
		cv::Ptr<cv::cuda::HOG> gpu_hog;
		cv::HOGDescriptor hog;
		Extract::IBackgroundSubtractor *subtractor;
		std::vector<cv::Mat> subtractedFrames;
		std::vector<cv::Mat> resizedFrames;
		std::vector<int> findSilhouetteOffset(std::vector<cv::Mat> frames);
		bool visualizeFlag;
	public:
		SilhouetteExtractor(int subtractionType = 0, bool visualizeFlag = false);
		std::vector<int> extract(std::vector<cv::Mat> frames);
		std::vector<cv::Mat> getResizedFrames();
	};

}