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

			virtual void Execute(std::vector<std::string> args, IApplicationContext* context, int position) = 0;
			virtual std::string ToString() = 0;
		};

		class HelpCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
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

			void ReadParameters(int argc, char** argv);
		};

		class SaveToDirecotryCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
			std::string ToString() override;
		};

		class CreteMirrorsCommand : public  ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
			std::string ToString() override;
		};

		class LearningModeCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
			std::string ToString() override;
		};

		class NueralNetPathCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
			std::string ToString() override;
		};

		class VisualizationCommand : public ICommand
		{
		public:
			void Execute(std::vector<std::string> args, IApplicationContext* context, int position) override;
			std::string ToString() override;
		};
	}
}
