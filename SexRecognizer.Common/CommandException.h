#pragma once
#include <exception>
#include <string>

namespace Common
{
	namespace Exceptions
	{
		class CommandException : public std::exception
		{
		public:
			virtual const char* what() const throw() override
			{
				return "Command error occured";
			}
		};

		class InvalidCommandException : public CommandException
		{
		private:
			std::string _providedCommand = "";
		public:

			InvalidCommandException(const std::string& cs)
				: _providedCommand(cs)
			{
			}

			const char* what() const throw() override 
			{
				return "Invalid command was provided";
			}
		};


		class InvalidParametersException : public CommandException
		{
		private:
			std::string _commandName = "";
			const char* msg;
		public:

			explicit InvalidParametersException(const std::string& cs)
				: _commandName(cs)
			{
			}

			const char* what() const throw() override{
				return "Invalid parameters";
			}
		};

	}
}

