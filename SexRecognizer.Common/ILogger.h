#pragma once
#include <string>
#include <vector>

namespace Common
{
	class ILogger
	{
	public:
		ILogger();
		virtual ~ILogger();
		virtual void Log(std::string msg, std::string sender = "");
		virtual void Error(std::string msg, std::string sender = "");
	};

	class DefaultLogger : public ILogger
	{
	};
}

