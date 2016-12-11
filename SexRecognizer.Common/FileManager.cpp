#include "FileManager.h"
#include <iomanip>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "IOException.h"


#ifdef __linux__
#include <sys/stat.h>
#elif _WIN32
#include <windows.h>
#endif


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

void FileManager::MakeDirectory(std::string path)
{
#ifdef __linux__
	const int dir_err = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err)
	{
		throw Exceptions::DirectoryCreationFailException();
	}
#elif _WIN32
	if (CreateDirectory(path.c_str(), NULL))
	{
		return;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		throw Exceptions::DirectoryExistsException();
	}
	else
	{
		throw Exceptions::DirectoryCreationFailException();
	}
#endif

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

