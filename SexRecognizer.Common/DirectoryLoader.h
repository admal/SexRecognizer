#pragma once
#include <string>
#include <vector>
#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"

namespace Common
{
	class DirectoryLoader
	{
	private:
		std::string directoryPath;

		//std::vector<std::string> GetFileNames();
	public:
		DirectoryLoader(std::string directoryPath);
		std::vector<cv::Mat> GetFrames();

		~DirectoryLoader();
	};
}

