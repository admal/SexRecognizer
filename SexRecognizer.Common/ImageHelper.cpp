#include "ImageHelper.h"

using namespace Common::Helpers;
using namespace std;
using namespace cv::cuda;
using namespace cv;

cv::Mat ImageHelper::mirrorImage(cv::Mat img)
{
	cv::Mat dst;
	cv::cuda::flip(img, dst, 1);
	return dst;
}

std::vector<cv::Mat> ImageHelper::mirrorImages(std::vector<cv::Mat> images)
{
	std::vector<cv::Mat> mirroredImages;
	for (auto image : images)
	{
		mirroredImages.push_back(mirrorImage(image));
	}
	return mirroredImages;
}