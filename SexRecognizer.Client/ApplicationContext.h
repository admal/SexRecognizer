#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../SexRecognizer.Common/IApplicationContext.h"
#include "../SexRecognizer.Common/IStrategy.h"
#include "../SexRecognizer.Biometrics/OpticalFlow.h"
#include "../SexRecognizer.Common/IOpticalFlow.h"

class ApplicationContext : public Common::IApplicationContext
{
private:
	std::string _videoPath;
	std::string _outputPath = ".\\output\\";
	std::string _neuralnetPath = ".\\model\\my-model";

	std::vector<std::vector<cv::Mat>> _resizedFrames;
	std::vector<std::vector<int>> _offsets;
	std::vector<std::vector<cv::Mat>> _opticalFlowFrames;
	Common::IOpticalFlow* _opticalFlowAlg;
	bool _mirrorFlag = false;
	bool _learningMode = false;
public:

	Common::IStrategy* detectorContext;
	Common::IStrategy* biometricsContext;
	Common::IStrategy* neuralNetContext;

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

	std::vector<std::vector<cv::Mat>>& resized_frames() override
	{
		return _resizedFrames;
	}

	void set_resized_frames(std::vector<std::vector<cv::Mat>> frames) override
	{
		_resizedFrames = std::move(frames);
	}

	std::vector<std::vector<int>>& offsets() override
	{
		return _offsets;
	}

	void set_offsets(std::vector<std::vector<int>> offsets) override
	{
		_offsets = std::move(offsets);
	}


	std::vector<std::vector<cv::Mat>>& optical_flow_frames() override
	{
		return _opticalFlowFrames;
	}

	void set_optical_flow_frames(std::vector<std::vector<cv::Mat>> vector) override
	{ 
		_opticalFlowFrames = std::move(vector);
	}

	Common::IOpticalFlow* optical_flow_alg() override
	{
		return _opticalFlowAlg;
	}

	void set_optical_flow_alg(Common::IOpticalFlow* i_optical_flow) override
	{
		_opticalFlowAlg = i_optical_flow;
	}

	void setMirrorFlag(bool flag)
	{
		_mirrorFlag = flag;
	}

	bool isMirrorFlag()
	{
		return _mirrorFlag;
	}

	void setLearningMode(bool flag) override
	{
		_learningMode = flag;
	}
	bool isInLearningMode() override
	{
		return _learningMode;
	}
	std::string& neuralnet_path()
	{
		return _neuralnetPath;
	}

	void set_neuralnet_path(std::string cs)
	{
		_neuralnetPath = std::move(cs);
	}
};

