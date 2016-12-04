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
		if (file[file.length() - 1] != '\\' )
		{
			file.append("\\");
		}
		file.append(MakeFilename(maxLenght, to_string(i)));
		file.append(extension);

		cv::imwrite(file, images[i]);
	}
}

string FileManager::MakeFilename(int maxLength, std::string sufix)
{
	std::ostringstream result;
	result  <<
		std::setfill('0') <<
		std::setw(maxLength) <<
		sufix;
	return result.str();
}
