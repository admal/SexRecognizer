#pragma once
#include "opencv2/core/mat.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/types.hpp"
#include <vector>


namespace Common 
{
	namespace Helpers 
	{
		class ImageHelper
		{
		public:
			static cv::Mat mirrorImage(cv::Mat img);
			static std::vector<cv::Mat> mirrorImages(std::vector<cv::Mat> images);
		};
	}
}
