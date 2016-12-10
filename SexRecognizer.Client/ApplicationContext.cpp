#define _CRT_SECURE_NO_DEPRECATE
#include "ApplicationContext.h"
#include "../SexRecognizer.Detector/DetectorContext.h"
#include "../SexRecognizer.Biometrics/BiometricsContext.h"
#include <iostream>

void ApplicationContext::Start()
{
	//this->_videoPath = "C:\\Users\\Adam\\Pictures\\inz-klatki";
	this->detectorContext = new DetectorContext();
	this->biometricsContext = new Context::BiometricsContext();

	//this->_outputPath = "C:\\Users\\Adam\\Pictures\\inz_output\\";
	this->_opticalFlowAlg = new OpticalFlow::FarnebackOpticalFlow();
	//this->setMirrorFlag(true);
	this->detectorContext->Execute(this);
	this->biometricsContext->Execute(this);
	std::cout << "[ FINISHED ] \n";
	//std::cout << "Enter to close...\n";
	//std::cin.get();
}
