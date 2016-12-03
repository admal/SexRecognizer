#include "OpticalFlow.h"
#include <opencv2/cudaoptflow.hpp>
#include <iostream>
#include "BiometricsContext.h"

using namespace OpticalFlow;
using namespace cv;

int OpticalFlow::FarnebackOpticalFlow::Calculate(cv::Mat* frame1, cv::Mat* frame2, cv::Mat* output)
{
	auto farn = cv::cuda::FarnebackOpticalFlow::create();

	cuda::GpuMat d_frame0(*frame1);
	cuda::GpuMat d_frame1(*frame2);

	cuda::GpuMat d_flow(frame1->size(), CV_32FC2);

	const int64 start = cv::getTickCount();

	farn->calc(d_frame0, d_frame1, d_flow);

	d_flow.download(*output);

	const double timeSec = (cv::getTickCount() - start) / cv::getTickFrequency();

	auto logger = Common::LoggerFactory::GetLogger();
	logger->Log(3, "Farn :", std::to_string(timeSec).c_str(), "sec");

	return 0;
}
