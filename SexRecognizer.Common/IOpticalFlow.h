#pragma once

#include "opencv2/core.hpp"
namespace Common
{
	class IOpticalFlow
	{
	public:
		virtual ~IOpticalFlow()
		{
		}
		virtual int Calculate(cv::Mat* frame1, cv::Mat* frame2, cv::Mat* output) = 0;
	};
	
}