#pragma once

#include "opencv2/core.hpp"

namespace OpticalFlow 
{
	class IOpticalFlow
	{
	public:
		virtual ~IOpticalFlow()
		{
		}
		virtual int Calculate(cv::Mat* frame1, cv::Mat* frame2, cv::Mat* output) = 0;
	};

	//different OpticalFlow algorithms implementations
	class FarnebackOpticalFlow : public IOpticalFlow
	{
	public:
		int Calculate(cv::Mat* frame1, cv::Mat* frame2, cv::Mat* output) override;
	};
}

