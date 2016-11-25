#pragma once
#include "../SexRecognizer.Common/ILogger.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"


namespace Extract {

	class ImageResizer{
	private:
		cv::Size size;
	public:
		int ImageResizer::resize(cv::Mat* img) const;
		ImageResizer(int width = 80, int height = 60);
		std::vector<cv::Mat> resizeFrames(std::vector<cv::Mat> frames) const;
	};

}