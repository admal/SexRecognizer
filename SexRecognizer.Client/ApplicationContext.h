#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../SexRecognizer.Common/IApplicationContext.h"
#include "../SexRecognizer.Common/IStrategy.h"

class ApplicationContext : public Common::IApplicationContext
{
private:
	std::string _videoPath;
	std::string _outputPath = "";

	std::vector<cv::Mat> _resizedFrames;
	std::vector<int> _offsets;
	std::vector<cv::Mat> _opticalFlowFrames;

public:

	Common::IStrategy* detectorContext;
	Common::IStrategy* biometricsContext;

	ApplicationContext(){};
	~ApplicationContext(){};

	void Start();


	std::string& video_path() override
	{
		return _videoPath;
	}

	void set_video_path(std::string videoPath) override
	{
		_videoPath = std::move(videoPath);
	}

	std::string& output_path() override
	{
		return _outputPath;
	}

	void set_output_path(std::string outputPath) override
	{
		_outputPath = std::move(outputPath);
	}

	std::vector<cv::Mat>& resized_frames() override
	{
		return _resizedFrames;
	}

	void set_resized_frames(std::vector<cv::Mat> frames) override
	{
		_resizedFrames = std::move(frames);
	}

	std::vector<int>& offsets() override
	{
		return _offsets;
	}

	void set_offsets(std::vector<int> offsets) override
	{
		_offsets = std::move(offsets);
	}
};

