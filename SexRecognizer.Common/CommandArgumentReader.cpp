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
	_possibleCommands->insert(std::make_pair("-l", new LearningModeCommand()));
	_possibleCommands->insert(std::make_pair("-h", new HelpCommand()));
	_possibleCommands->insert(std::make_pair("-p", new SaveToDirecotryCommand()));
	_possibleCommands->insert(std::make_pair("-m", new CreteMirrorsCommand()));
	_possibleCommands->insert(std::make_pair("-n", new NueralNetPathCommand()));
}


CommandArgumentsReader::~CommandArgumentsReader()
{
	delete _possibleCommands;
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

				command->Execute(args, _context, i);
			}
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
	return "Path to directory where optical flow frames should be saved (in learning mode)";
}

void CreteMirrorsCommand::Execute(std::vector<std::string> args, IApplicationContext* context, int position)
{
	context->setMirrorFlag(true);
}

std::string CreteMirrorsCommand::ToString()
{
	return "Generate mirrored in Y axis movie (in learning mode)";
}

void HelpCommand::Execute(std::vector<string> args, IApplicationContext* context, int position)
{
	std::cout << "Help" << std::endl;
}

std::string HelpCommand::ToString()
{
	return "Show help options";
}

void LearningModeCommand::Execute(std::vector<std::string> args, IApplicationContext* context, int position)
{
	context->setLearningMode(true);
}

std::string LearningModeCommand::ToString()
{
	return "Start application in learning mode (it will generate from input video set of frames representing optical flow)";
}

void NueralNetPathCommand::Execute(std::vector<std::string> args, IApplicationContext* context, int position)
{
	if (args.size() - 1 <= position)
	{
		throw Exceptions::InvalidParametersException("-n");
	}
	string path = args[position + 1];
	if (path[0] == '-') //it means that no arguments are provided
	{
		throw Exceptions::InvalidParametersException("-n");
	}
	auto logger = LoggerFactory::GetLogger();
	logger->Log(2, "Neural network path:", path);
	context->set_neuralnet_path(path);
}

std::string NueralNetPathCommand::ToString()
{
	return "Path to the model of neural network.";
}

void CommandArgumentsReader::Usage()
{
	std::cout << "Usage: directory_path <arguments> " << std::endl;
	std::cout << "directory_path : directory where frames (in .jpg format) of the video are stored" << std::endl;
	std::cout << "Arguments: " << std::endl;
	for (auto it = _possibleCommands->begin(); it != _possibleCommands->end(); ++it)
		std::cout << it->first << " : " << it->second->ToString() << '\n';
}

