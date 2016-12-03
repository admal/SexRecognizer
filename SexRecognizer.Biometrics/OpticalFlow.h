#pragma once

#include "opencv2/core.hpp"
#include "../SexRecognizer.Common/IOpticalFlow.h"

namespace OpticalFlow 
{


	//different OpticalFlow algorithms implementations
	class FarnebackOpticalFlow : public Common::IOpticalFlow
	{
	public:
		int Calculate(cv::Mat* frame1, cv::Mat* frame2, cv::Mat* output) override;
	};
}

