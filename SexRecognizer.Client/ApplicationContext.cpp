#define _CRT_SECURE_NO_DEPRECATE
#include "ApplicationContext.h"
#include "../SexRecognizer.Detector/DetectorContext.h"
#include "../SexRecognizer.Biometrics/BiometricsContext.h"
#include <iostream>
#include "../SexRecognizer.NeuralNet/NeuralNetContext.h"

void ApplicationContext::Start()
{
	auto isLeraningMode = this->_learningMode;


	this->detectorContext = new DetectorContext();
	this->biometricsContext = new Context::BiometricsContext();

	this->_opticalFlowAlg = new OpticalFlow::FarnebackOpticalFlow();
	this->detectorContext->Execute(this);
	this->biometricsContext->Execute(this);
	
	if (!isLeraningMode)
	{
		this->neuralNetContext = new Context::NeuralNetContext();
		this->neuralNetContext->Execute(this);
	}

	std::cout << "[ FINISHED ] \n";
}
