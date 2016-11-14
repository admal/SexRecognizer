#include "CommandArgumentsReader.h"	
#include "BiometricsContext.h"
using namespace Common;

CommandArgumentsReader::CommandArgumentsReader()
{
	possibleCommands = new std::map<std::string, ICommand*>();
	//possibleCommands->insert(std::make_pair("custom", new ))
	possibleCommands->insert(std::make_pair("-h", new HelpCommand()));
}


CommandArgumentsReader::~CommandArgumentsReader()
{
}

ReaderReturnStatus CommandArgumentsReader::ReadParameters(int argc, char** argv)
{
	auto context = Context::BiometricsContext::getInstance();
	auto logger = context->logger;

	if (argc < 2)
	{
		Usage();
		return InvalidParameters;
	}
	/*std::string msg = "Path: ";
	msg.append(argv[1]);*/
	logger->Log(2, "Path:", argv[1]);
	context->videoPath = argv[1];

	//std::cout << "path: " << argv[1] << std::endl;
	for (int i = 2; i < argc; i++)
	{
		try
		{
			auto command = possibleCommands->at(argv[i]);
			command->Execute(argv); //powinno braæ wszystkie argumenty do koñca lub do nastêpnej komendy
			i++;
		}
		catch (std::out_of_range e)
		{
			logger->Error("Command not found, call -h to show possible commands\n");
			//std::cout << "Command not found, call -h to show possible commands\n";
		}
	}

	return OK;
}

void HelpCommand::Execute(char** args)
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
	
	for (auto it = possibleCommands->begin(); it != possibleCommands->end(); ++it)
		std::cout << it->first << " : " << it->second->ToString() << '\n';
}
