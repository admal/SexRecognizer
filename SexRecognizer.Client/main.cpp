#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "ApplicationContext.h"
#include "../SexRecognizer.Detector/DetectorContext.h"

int main(int argc, char* argv[])
{
	ApplicationContext* context = new ApplicationContext();
	context->Start();
}
