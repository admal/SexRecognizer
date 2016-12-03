#include "FileManager.h"
#include <iomanip>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace Common::IO;
using namespace std;

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

void FileManager::SaveOuptut(string filepath, vector<cv::Mat> images)
{
	for (int i = 0; i < images.size(); i++)
	{
		string file = filepath;
		file.append(MakeFilename(maxLenght, to_string(i + 1)));
		file.append(extension);

		cv::imwrite(file, images[i]);
	}
}

string FileManager::MakeFilename(int maxLength, std::string sufix)
{
	std::ostringstream result;
	result  <<
		std::setfill('0') <<
		std::setw(maxLength - sufix.length()) <<
		sufix;
	return result.str();
}
