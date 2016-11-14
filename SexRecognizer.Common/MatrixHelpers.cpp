#include "MatrixHelpers.h"

using namespace Common::Helpers;

cv::Mat MatrixHelpers::GetSquareSubmatrix(cv::Mat matrix , int squareSize, int startX, int startY)
{
	cv::Mat submatrix = matrix(cv::Range(startX, startX + squareSize), cv::Range(startY, startY + squareSize));

	return submatrix;
}

