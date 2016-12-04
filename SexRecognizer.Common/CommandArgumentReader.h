#pragma once
#include <string>
#include <vector>
#include <map>
#include "../SexRecognizer.Client/ApplicationContext.h"
#include "ILogger.h"

namespace Common
{
	namespace Command
	{
		enum ReaderReturnStatus
		{
			OK, InvalidCommand, InvalidParameters
		};

		class ICommand
		{
		public:
			virtual ~ICommand()
			{
			}

			virtual void Execute(std::vector<std::string> args, IApplicationContext* context) = 0;
			virtual std::string ToString() = 0;
		};

		class HelpCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context) override;
			std::string ToString() override;
		};

		class CommandArgumentsReader
		{
		private:
			std::map<std::string, ICommand*>* _possibleCommands;
			IApplicationContext* _context;
			ILogger* _logger;
			void Usage();

		public:
			CommandArgumentsReader(IApplicationContext* context);
			~CommandArgumentsReader();

			ReaderReturnStatus ReadParameters(int argc, char** argv);
		};

		class SaveToDirecotryCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context) override;
			std::string ToString() override;
		};

	}
}
