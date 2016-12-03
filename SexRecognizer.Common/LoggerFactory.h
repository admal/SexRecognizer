#pragma once
#include "ILogger.h"

namespace Common {
	class LoggerFactory
	{
	private:
		bool file = false;
	public:
		LoggerFactory(bool file = false);
		~LoggerFactory();

		static ILogger* GetLogger();
	};

}