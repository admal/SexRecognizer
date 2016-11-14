#pragma once
#include <string>
#include <vector>
#include <stdarg.h>
namespace Common
{
	class ILogger
	{
	public:
		ILogger();
		virtual ~ILogger();
		virtual void Log(std::string msg, std::string sender = "");
		virtual void Error(std::string msg, std::string sender = "");
		/*
		*	Function takes variadic number of char* variables
		*	(std::string should be casted to char* by c_str() method!)
		*/
		virtual void Log(int count, ...);
	};

	class DefaultLogger : public ILogger
	{
	};
}

