#pragma once
#include <string>
#include "../SexRecognizer.Common/ILogger.h"
#include "OpticalFlow.h"

namespace OpticalFlow{
	class IOpticalFlow;
}

namespace Context
{
	class BiometricsContext
	{
	private:
		//static bool instanceFlag;
		static BiometricsContext *instance;
		BiometricsContext()
		{
			//private constructor
			//instanceFlag = false;
			logger = new Common::DefaultLogger();
			opticalFlowAlg = new OpticalFlow::FarnebackOpticalFlow(); //TODO: w ³adowaæ poprzez parametr jaki algorytm u¿ywaæ
		}

	public:
		std::string videoPath;
		Common::ILogger* logger;
		OpticalFlow::IOpticalFlow* opticalFlowAlg;

		static BiometricsContext* getInstance();
		~BiometricsContext()
		{
			delete logger;
			delete opticalFlowAlg;
			//instanceFlag = false;
		}
	};
}
