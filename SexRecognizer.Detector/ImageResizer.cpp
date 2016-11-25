#include "ImageResizer.h"

using namespace Extract;
using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace Common;


ImageResizer::ImageResizer(int width, int height){
	this->size = cv::Size(width, height);
}

int ImageResizer::resize(cv::Mat* img) const
{
	cuda::GpuMat input(*img);
	cuda::GpuMat output;

	cuda::resize(input, output, this->size); // resize
	
	output.download(*img);

	input.release();
	output.release();
	
	return 0;
}

std::vector<cv::Mat> ImageResizer::resizeFrames(std::vector<cv::Mat> frames) const
{
	//load images from folder to vector
	for (int i = 0; i < frames.size(); i++){
		resize(&frames[i]);
	}

	return frames;
}
