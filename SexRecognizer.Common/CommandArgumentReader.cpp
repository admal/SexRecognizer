#include "CommandArgumentReader.h"
#include <iostream>
#include "LoggerFactory.h"
#include "CommandException.h"
using namespace std;
using namespace Common;
using namespace Common::Command;

CommandArgumentsReader::CommandArgumentsReader(IApplicationContext* context)
{
	this->_context = context;
	this->_logger = LoggerFactory::GetLogger();
	_possibleCommands = new std::map<std::string, ICommand*>();
	//possibleCommands->insert(std::make_pair("custom", new ))
	_possibleCommands->insert(std::make_pair("-h", new HelpCommand()));
	_possibleCommands->insert(std::make_pair("-p", new SaveToDirecotryCommand()));
}


CommandArgumentsReader::~CommandArgumentsReader()
{
}

void CommandArgumentsReader::ReadParameters(int argc, char** argv)
{
	if (argc < 2)
	{
		Usage();
		throw Exceptions::CommandException();
	}

	_logger->Log(2, "Path:", argv[1]);
	_context->set_video_path(argv[1]);

	std::vector<string> args;
	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	for (int i = 2; i < argc; i++)
	{
		try
		{
			string commandString = args[i];
			if (commandString[0] == '-')
			{
				auto command = _possibleCommands->at(args[i]);

				command->Execute(args, _context, i); //powinno braæ wszystkie argumenty do koñca lub do nastêpnej komendy
			}
			i++;
		}
		catch (std::out_of_range e)
		{
			throw Exceptions::InvalidCommandException(args[i]);
		}
	}

}

void SaveToDirecotryCommand::Execute(std::vector<string> args, IApplicationContext* context, int position)
{
	if (args.size() - 1 <= position)
	{
		throw Exceptions::InvalidParametersException("-p");
	}
	string path = args[position + 1];
	if (path[0] == '-') //it means that no arguments are provided
	{
		throw Exceptions::InvalidParametersException("-p");
	}
	auto logger = LoggerFactory::GetLogger();
	logger->Log(2, "Optical flow path:", path);

	context->set_output_path(path);
}

std::string SaveToDirecotryCommand::ToString()
{
	return "Path to directory where optical flow frames should be saved";
}

void HelpCommand::Execute(std::vector<string> args, IApplicationContext* context, int position)
{
	std::cout << "Help" << std::endl;
}

std::string HelpCommand::ToString()
{
	return "Show help options";
}

void CommandArgumentsReader::Usage()
{
	std::cout << "Usage: directory_path <arguments> " << std::endl;

	for (auto it = _possibleCommands->begin(); it != _possibleCommands->end(); ++it)
		std::cout << it->first << " : " << it->second->ToString() << '\n';
}