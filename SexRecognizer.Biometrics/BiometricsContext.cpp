#include "BiometricsContext.h"
using namespace Context;

BiometricsContext* BiometricsContext::instance = nullptr;

BiometricsContext* BiometricsContext::getInstance()
{
	if (instance == nullptr)
	{
		instance = new BiometricsContext();
	}
	return instance;
}
