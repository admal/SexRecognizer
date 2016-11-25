#include "BackgroundSubtractor.h"

using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace Common;
using namespace Extract;


std::vector<cv::Mat> Extract::BackgroundSubtractorMOG2::subtract(std::vector<cv::Mat> frames) // change to use CUDA
{

	static int history = 1;
	static int threshold = 64;
	static bool detectShadow = false;

	std::vector<cv::Mat> subFrames;
	cv::Ptr<BackgroundSubtractor> subtractor = cv::createBackgroundSubtractorMOG2(history, threshold, detectShadow);
	cv::Mat fgMask;
	string name;
	for (int i = 0; i < frames.size(); i++)
	{
		subtractor->apply(frames[i], fgMask);
		cv::Mat m;
		fgMask.copyTo(m);
		subFrames.push_back(m);
//		name = "sub" + to_string(i) + ".png";
//		cv::imwrite(name, m);
	}

	return subFrames;
	// TODO: remove cause useless or rewrite for GPU 
	//subtract background
	//	auto mog2 = cuda::createBackgroundSubtractorMOG2(100, false);
	//	auto fgMask = new cv::Mat();
	//	std::vector<cv::Mat> subFrames;
	//
	////	auto mog2 = cuda::createBackgroundSubtractorMOG2(100, false);
	//	auto img = cv::Mat();
	//
	//	for (int i = 0; i < frames.size(); i++)
	//	{
	//		mog2->apply(cv::InputArray(frames[i]), *fgMask);
	//		imwrite("gg" + to_string(i) + ".png", *fgMask);
	//		subFrames.push_back(*fgMask);
	//	}
}
