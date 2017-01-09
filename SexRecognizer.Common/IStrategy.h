#pragma once
#include "IApplicationContext.h"
#include "../SexRecognizerGUI/logger.h"
#undef B0


namespace Common
{
	class IStrategy
	{
	public:
		virtual ~IStrategy(){}

		virtual void Execute(IApplicationContext* context) =0;
		virtual void Execute(IApplicationContext* context, SexRecognizer::Logger *logger) = 0;
	};
}
