#include "recognizer.h"
#include "../SexRecognizer.Client/ApplicationContext.h"
#include "../SexRecognizer.Detector/DetectorContext.h"
#include "../SexRecognizer.Common/IOException.h"

SexRecognizer::Recognizer::Recognizer(Logger* logger)
{
    this->logger = logger;
}

int SexRecognizer::Recognizer::loadImages(QString filePath){
	this->videoPath = filePath.toStdString();
	logger->log("PATH TO VIDEO: ");
	logger->log(filePath);
	try{
		app = new ApplicationContext();
	} catch (...)
	{
		logger->error("app context dependency fail");
		return 0;
	}
	app->set_video_path(videoPath);
	try{
		DetectorContext *detector = new DetectorContext();
		detector->Execute(app);
	}
	catch (Exceptions::DirectoryExistsException e)
	{
		logger->error(e.what());
		logger->error("error");
	}
	catch (...)
	{
		logger->error("everything failed");
	}
	logger->log("We made it through.");
    return 0;
}
int SexRecognizer::Recognizer::process(){
    return 0;
}
SexRecognizer::Recognizer::~Recognizer(){
}
