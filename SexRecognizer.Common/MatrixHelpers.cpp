#include "MatrixHelpers.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>

using namespace Common::Helpers;

cv::Mat MatrixHelpers::GetSquareSubmatrix(cv::Mat matrix , int squareSize, int startX, int startY)
{
	cv::Mat submatrix = matrix(cv::Range(startY, startY + squareSize), cv::Range(startX, startX + squareSize));

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
