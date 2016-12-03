#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "ApplicationContext.h"
#include "../SexRecognizer.Common/CommandArgumentReader.h"


int main(int argc, char* argv[])
{
	ApplicationContext* context = new ApplicationContext();

	Common::Command::CommandArgumentsReader reader(context);
	reader.ReadParameters(argc, argv);
	context->Start();
}
