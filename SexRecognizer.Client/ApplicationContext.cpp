#define _CRT_SECURE_NO_DEPRECATE
#include "ApplicationContext.h"
#include "../SexRecognizer.Detector/DetectorContext.h"

void ApplicationContext::Start()
{
	this->_videoPath = "C:\\Users\\Adam\\Pictures\\inz-klatki";
	this->detectorContext = new DetectorContext();
	this->detectorContext->Execute(this);


}
