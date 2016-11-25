#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include "../SexRecognizer.Common/ILogger.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/matx.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/core/bufferpool.hpp"
#include "opencv2/core/mat.inl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
namespace Extract{

	class IBackgroundSubtractor
	{
	public:
		virtual ~IBackgroundSubtractor()
		{
		}

		virtual std::vector<cv::Mat> subtract(std::vector<cv::Mat> frames) =0;
	};

	class BackgroundSubtractorMOG2 : public IBackgroundSubtractor 
	{
	public:
		std::vector<cv::Mat> subtract(std::vector<cv::Mat> frames) override;
	};
}