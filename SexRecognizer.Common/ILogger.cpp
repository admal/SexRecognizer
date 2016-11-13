#include "ILogger.h"
#include <iostream>

using namespace Common;

ILogger::ILogger()
{
}


ILogger::~ILogger()
{
}

void ILogger::Log(std::string msg, std::string sender)
{
	std::cout << "[Log] : " << msg << ";";
	if (sender != "")
		std::cout << " From: " << sender;
	std::cout << std::endl;
}

void ILogger::Error(std::string msg, std::string sender)
{
	std::cout << "[Error] : " << msg << ";";
	if (sender != "")
		std::cout << " From: " << sender;
	std::cout << std::endl;
}
