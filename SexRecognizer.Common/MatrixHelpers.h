#pragma once
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"

namespace Common
{
	namespace Helpers
	{
		class MatrixHelpers
		{
		public:
			static cv::Mat GetSquareSubmatrix(cv::Mat matrix, int width, int height, int startX, int startY);
			static std::vector<cv::Mat> GetGrayscaleImages(std::vector<cv::Mat> colorImages);
		};		
	}
}
