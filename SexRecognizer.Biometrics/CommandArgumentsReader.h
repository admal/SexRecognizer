#pragma once
#include <string>
#include <map>
#include <iostream>


namespace Common
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

		virtual void Execute(char** arguments) =0;
		virtual std::string ToString() = 0;
	};

	class HelpCommand : public ICommand
	{
	public:
		void Execute(char** arguments) override;
		std::string ToString() override;
	};

	class CommandArgumentsReader
	{
	private:
		std::map<std::string, ICommand*>* possibleCommands;
		
		void Usage();
		
	public:
		CommandArgumentsReader();
		~CommandArgumentsReader();

		ReaderReturnStatus ReadParameters(int argc, char** argv);
	};

}

