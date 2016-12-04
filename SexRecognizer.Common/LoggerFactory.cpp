#include "LoggerFactory.h"

using namespace Common;

LoggerFactory::LoggerFactory(bool file)
{
	this->file = file;
}


LoggerFactory::~LoggerFactory()
{
}

ILogger* LoggerFactory::GetLogger()
{
	auto logger = new DefaultLogger();
	return logger;	
}
