#pragma once
#include <opencv2/core/mat.hpp>
#include "opencv2/cudaoptflow.hpp"
#include "opencv2/cudaarithm.hpp"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "OpticalFlow.h"
#include "../SexRecognizer.Common/MatrixHelpers.h"
#include "../SexRecognizer.Common/IOpticalFlow.h"

using namespace std;
using namespace cv;
using namespace Common;

class OpticalFlowSolver
{
public:
	~OpticalFlowSolver();

	OpticalFlowSolver(const vector<int>& is, const vector<cv::Mat>& mats, IOpticalFlow* i_optical_flow)
		: _offsets(is),
		  _frames(mats),
		  _opticalFlow(i_optical_flow)
	{
	}

	vector<Mat> DoCompute(int width, int height)
	{
		auto logger = LoggerFactory::GetLogger();
		logger->Log("Computation started...");
		logger->Log(2, "Loaded frames:", to_string(_frames.size()).c_str());

		vector<cv::Mat> opticalFlowsMats;

		for (int i = 0; i < _frames.size() - 1; i++)
		{
			Mat output;
			_opticalFlow->Calculate(&_frames[i], &_frames[i + 1], &output);
			if (_offsets[i] >= 0)
			{
				Mat slicedOutput = Helpers::MatrixHelpers::GetSquareSubmatrix(output, width, height, _offsets[i], 0);

				auto frame = getOFFrame(slicedOutput);

				opticalFlowsMats.push_back(frame);
			}
		}

		return opticalFlowsMats;
	}

private:
	vector<int> _offsets;
	vector<cv::Mat> _frames;
	IOpticalFlow* _opticalFlow;

	bool isFlowCorrect(cv::Point2f u)
	{
		return !cvIsNaN(u.x) && !cvIsNaN(u.y) && fabs(u.x) < 1e9 && fabs(u.y) < 1e9;
	}

	void drawOpticalFlow(const Mat_<float>& flowx, const Mat_<float>& flowy, Mat& dst, float maxmotion = -1)
	{
		dst.create(flowx.size(), CV_8UC3);
		dst.setTo(Scalar::all(0));

		// determine motion range:
		float maxrad = maxmotion;
		//find max value of optical flow
		if (maxmotion <= 0)
		{
			maxrad = 1;
			for (int y = 0; y < flowx.rows; ++y)
			{
				for (int x = 0; x < flowx.cols; ++x)
				{
					Point2f u(flowx(y, x), flowy(y, x));

					if (!isFlowCorrect(u))
						continue;

					maxrad = max(maxrad, sqrt(u.x * u.x + u.y * u.y));
				}
			}
		}
		//represent as pixels optical flow values (in 2 chanels)
		for (int y = 0; y < flowx.rows; ++y)
		{
			for (int x = 0; x < flowx.cols; ++x)
			{
				Point2f u(flowx(y, x), flowy(y, x));

				if (isFlowCorrect(u))
					dst.at<Vec3b>(y, x) = GetPixel(u.x, u.y, maxrad); 
			}
		}
	}

	Vec3d GetPixel(double x, double y, double max)
	{
		return Vec3d(0, 128 + (y / max * 255), 128 + (x / max * 255));//BGR
	}

	/*
	*	Get optical flow frame
	*/
	Mat getOFFrame(const Mat& d_flow)
	{
		cuda::GpuMat planes[2];
		cuda::split(d_flow, planes);

		Mat flowx(planes[0]);
		Mat flowy(planes[1]);

		Mat out;
		drawOpticalFlow(flowx, flowy, out, 5); //TODO: przekminiæ ten maxmotion
		return out;
	}
};

