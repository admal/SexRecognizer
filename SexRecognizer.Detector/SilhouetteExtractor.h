#pragma once
#include "BackgroundSubtractor.h"


namespace Extract {

	class SilhouetteExtractor {
	private:
		Extract::IBackgroundSubtractor *subtractor;
		std::vector<cv::Mat> subtractedFrames;
		std::vector<cv::Mat> resizedFrames;
		std::vector<int> findSilhouetteOffset(std::vector<cv::Mat> frames);

	public:
		SilhouetteExtractor(int subtractionType = 0);
		std::vector<int> extract(std::vector<cv::Mat> frames);
		std::vector<cv::Mat> getResizedFrames();
	};

}