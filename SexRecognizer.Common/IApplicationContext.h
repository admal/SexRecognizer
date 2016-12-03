#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

namespace Common
{
	class IApplicationContext
	{
	public:
		virtual ~IApplicationContext(){};

		virtual std::string& video_path() = 0;

		virtual void set_video_path(std::string cs) = 0;

		virtual std::string& output_path() = 0;

		virtual void set_output_path(std::string cs) = 0;

		virtual std::vector<cv::Mat>& resized_frames() = 0;

		virtual void set_resized_frames(std::vector<cv::Mat> vector) = 0;

		virtual std::vector<int>& offsets() = 0;

		virtual void set_offsets(std::vector<int> is) = 0;
	};

}