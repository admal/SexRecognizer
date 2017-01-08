#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "ApplicationContext.h"
#include "../SexRecognizer.Common/CommandArgumentReader.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include <iostream>


int main(int argc, char* argv[])
{
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
		//std::getchar();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
