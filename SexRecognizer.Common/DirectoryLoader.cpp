#include "DirectoryLoader.h"
#include "PathHelper.h"

using namespace Common;
using namespace Common::Helpers;
DirectoryLoader::DirectoryLoader(std::string directoryPath)
{
	this->directoryPath = directoryPath;
}

std::vector<cv::Mat> DirectoryLoader::GetFrames(bool grayscale)
{
	std::vector<cv::Mat> frames;

	const cv::String pathPattern = directoryPath.append("\\%03d.jpg"); //musz¹ byæ numerowane od 1!

	cv::VideoCapture cap(pathPattern);
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
			break;
		}
	}

	return frames;
}

DirectoryLoader::~DirectoryLoader()
{
}

