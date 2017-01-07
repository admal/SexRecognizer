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
	std::cout << "[LOG] : " << msg << ";";
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

void ILogger::Log(int count, ...)
{
	va_list ap;
	va_start(ap, count); //Requires the last fixed parameter (to get the address)
	//std::string log = "[LOG] : ";
	std::cout << "[LOG] : ";
	for (int j = 0; j < count; j++)
	{
		 //Requires the type to cast to. Increments ap to the next argument.
		/*log.append(va_arg(ap, char*));
		log.append(" ");*/
		std::cout << va_arg(ap, char*) << " ";
	}
	va_end(ap);
	/*log.append(";\n");*/
	std::cout << ";" << std::endl;
}
