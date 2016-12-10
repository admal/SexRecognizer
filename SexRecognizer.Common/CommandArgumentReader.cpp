#include "CommandArgumentReader.h"
#include <iostream>
#include "LoggerFactory.h"
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

ReaderReturnStatus CommandArgumentsReader::ReadParameters(int argc, char** argv)
{
	if (argc < 2)
	{
		Usage();
		return InvalidParameters;
	}

	_logger->Log(2, "Path:", argv[1]);
	_context->set_video_path(argv[1]);
	_context->setMirrorFlag(true); // MIRROR FLAG SET
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

				command->Execute(args, _context); //powinno braæ wszystkie argumenty do koñca lub do nastêpnej komendy
			}
			i++;
		}
		catch (std::out_of_range e)
		{
			_logger->Error("Command not found, call -h to show possible commands\n");
			return InvalidCommand;
		}
	}

	return OK;
}

void SaveToDirecotryCommand::Execute(std::vector<string> args, IApplicationContext* context)
{
	vector<string>::iterator searched = std::find(args.begin(), args.end(), "-p");
	++searched;
	auto logger = LoggerFactory::GetLogger();
	logger->Log(2, "Optical flow path:", searched);

	context->set_output_path(*searched);
}

std::string SaveToDirecotryCommand::ToString()
{
	return "Path to directory where optical flow frames should be saved";
}

void HelpCommand::Execute(std::vector<string> args, IApplicationContext* context)
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