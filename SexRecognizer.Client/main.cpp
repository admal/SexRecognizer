#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "ApplicationContext.h"
#include "../SexRecognizer.Common/CommandArgumentReader.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;

	std::cout << "This program was started at: " << Hour << ":" << Min << ":" << Sec << std::endl;
	ApplicationContext* context = new ApplicationContext();

	Common::Command::CommandArgumentsReader reader(context);
	auto logger = Common::LoggerFactory::GetLogger();
	try
	{
		reader.ReadParameters(argc, argv);
		context->Start();
	}
	catch (std::exception& e)
	{
		logger->Error(e.what());
		std::getchar();
		return EXIT_FAILURE;
	}
	time_t currentTime1;
	struct tm *localTime1;
	time(&currentTime1);                   // Get the current time
	localTime1 = localtime(&currentTime1);  // Convert the current time to the local time
	int Hour1 = localTime1->tm_hour;
	int Min1 = localTime1->tm_min;
	int Sec1 = localTime1->tm_sec;

	std::cout << "Ended at: " << Hour1 << ":" << Min1 << ":" << Sec1 << std::endl;
	return EXIT_SUCCESS;
}
