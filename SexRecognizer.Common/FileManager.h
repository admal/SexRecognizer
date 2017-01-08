#pragma once
#include <string>
#include <vector>
#include "opencv2/core.hpp"

namespace Common
{
	namespace IO
	{
		class FileManager
		{
		public:
			FileManager();
			~FileManager();

			void SaveOuptut(std::string filepath, std::vector<cv::Mat> images);
			static void MakeDirectory(std::string path);

		private:
			const std::string extension = ".png";
			const int maxLenght = 3;
			std::string MakeFilename(int maxLength, std::string sufix);
		};
	}
}
