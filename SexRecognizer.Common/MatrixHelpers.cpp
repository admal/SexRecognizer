#include "MatrixHelpers.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>

using namespace Common::Helpers;

cv::Mat MatrixHelpers::GetSquareSubmatrix(cv::Mat matrix , int width, int height, int startX, int startY)
{
	cv::Mat submatrix = matrix(cv::Range(startY, startY + height), cv::Range(startX, startX + width));

	return submatrix;
}

std::vector<cv::Mat> MatrixHelpers::GetGrayscaleImages(std::vector<cv::Mat> colorImages)
{
	std::vector<cv::Mat> grayImages;

	for (int i = 0; i < colorImages.size(); i++)
	{
		cv::Mat grayMat;
		cv::cvtColor(colorImages[i], grayMat, cv::COLOR_BGR2GRAY);
		grayImages.push_back(grayMat);
	}

	return grayImages;
}
