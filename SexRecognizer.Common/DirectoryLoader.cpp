#include "DirectoryLoader.h"
#include "PathHelper.h"
#include "LoggerFactory.h"

using namespace Common;
using namespace Common::Helpers;
DirectoryLoader::DirectoryLoader(std::string directoryPath)
{
	this->directoryPath = directoryPath;
}

std::vector<cv::Mat> DirectoryLoader::GetFrames(bool grayscale)
{
	std::vector<cv::Mat> frames;


	const cv::String pathPattern = directoryPath.append("\\%03d.jpg");

	cv::VideoCapture cap(pathPattern);
	if (!cap.isOpened())
	{
		cap.release();
		exit(EXIT_FAILURE); //do not know why exception doesnt work
		//throw DirectoryLoadingException();
	}
	while (cap.isOpened())
	{
		cv::Mat img;
		if (cap.read(img))
		{
			if (grayscale)
			{
				cv::Mat grayscaleImg;
				cv::cvtColor(img, grayscaleImg, cv::COLOR_BGR2GRAY);
				frames.push_back(grayscaleImg);
			}
			else
			{
				frames.push_back(img);
			}
		}
		else
		{
			throw DirectoryLoadingException();
		}
	}
	
	return frames;
}

DirectoryLoader::~DirectoryLoader()
{
}

