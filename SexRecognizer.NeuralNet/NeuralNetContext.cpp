#include "NeuralNetContext.h"
#include "../SexRecognizer.Common/LoggerFactory.h"

void NeuralNetContext::Execute(Common::IApplicationContext* context)
{
	auto logger = Common::LoggerFactory::GetLogger();
	logger->Log("Neural network started");
	//w��rz tu rzeczy Piotrze
	logger->Log("Neural network finished");
}
