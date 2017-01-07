#pragma once
#include <string>
#include <vector>
#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/imgproc/imgproc.hpp>

namespace Common
{
	class DirectoryLoader
	{
	private:
		std::string directoryPath;

		//std::vector<std::string> GetFileNames();
	public:
		DirectoryLoader(std::string directoryPath);
		std::vector<cv::Mat> GetFrames(bool grayscale = false);

		~DirectoryLoader();
	};

	class DirectoryLoadingException : std::exception
	{
	public:
		const char* what() const override
		{
			return "Could not load given directory";
		}
	};
}

