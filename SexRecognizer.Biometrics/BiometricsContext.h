#pragma once
#include <string>
#include "../SexRecognizer.Common/ILogger.h"
#include "OpticalFlow.h"
#include "../SexRecognizer.Common/IStrategy.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "../SexRecognizer.Common/IOpticalFlow.h"

using namespace Common;
namespace Context
{
	class BiometricsContext : public IStrategy
	{


	public:
		BiometricsContext(){}
		~BiometricsContext(){}
		void Execute(IApplicationContext* context) override;
	};
}
