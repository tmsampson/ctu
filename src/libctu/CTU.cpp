#include "CTU.h"
#include "CommandMgr.h"
#include "Utils.h"
#include "TaskList.h"
#include <string>
#include <map>
#include <iostream>

// CTU Commands
#include "commands/CmdAdd.h" // add

static ConfigFile* pConfigFile;
static CTU::CommandMgr commandMgr;
static const std::string JK_CURRENT_TASK_LIST = "currentTaskList";
static const std::string JK_VERBOSE           = "verbose";
static const std::string JK_BULLET            = "bullet";

bool CTU::RunStartupChecks(ConfigFile* pConfig)
{
	pConfigFile = pConfig;

	// Ensure values are set OR default
	pConfigFile->Set<bool>(JK_VERBOSE, pConfigFile->Get<bool>(JK_VERBOSE, false));
	pConfigFile->Set<std::string>(JK_BULLET, pConfigFile->Get<std::string>(JK_BULLET, "> "));
	pConfigFile->Save();

	// Get path to current task list
	std::string taskListPath = pConfigFile->Get<std::string>(JK_CURRENT_TASK_LIST);

	// Is the current task list set?
	if(!taskListPath.empty())
		return true;

	Utils::PrintLine(Utils::EColour::YELLOW, "WARNING: No task list is currently set.");

	do
	{
		Utils::PrintLine("Where would you like your task list to be created? (leave blank for default)");
		Utils::Print("Task List Path: ");
		std::getline(std::cin, taskListPath);

		if(!taskListPath.empty())
		{
			taskListPath = Utils::StringTrim(taskListPath, ".\\/");
			if(!Utils::DirectoryExists(taskListPath))
				Utils::PrintLine(Utils::EColour::RED, "ERROR: The directory specified does not exist, please try again");
			continue;
		}

		taskListPath = Utils::GetDefaultTaskListDirectory();
	}
	while(!Utils::DirectoryExists(taskListPath));

	taskListPath = taskListPath + Utils::PATH_SEPARATOR + "tasks.txt";
	Utils::Print("Creating %s    ", taskListPath.c_str());
	if(!Utils::TouchFile(taskListPath))
	{
		Utils::PrintLine(Utils::EColour::RED, "FAIL");
		return false;
	}

	Utils::PrintLine(Utils::EColour::GREEN, "SUCCESS\r\n");
	pConfigFile->Set<std::string>(JK_CURRENT_TASK_LIST, taskListPath);

	return true;
}

void PrintIncorrectUsage(const std::string& commandName = "")
{
	if(commandName.size())
		Utils::PrintLine(Utils::EColour::RED, "ctu: unknown command '%s'", commandName.c_str());
	Utils::PrintLine("CTU Command-line Task Utility");
	Utils::PrintLine("\r\nbasic commands:\r\n");
	commandMgr.PrintCommandSummaries();
}

int CTU::Begin(const std::vector<std::string>& args)
{
	// Register all commands
	commandMgr.RegisterCommand<CTU::Commands::CmdAdd>(); // add

	if(!args.size())
	{
		PrintIncorrectUsage();
		return -1;
	}

	// Does command exist?
	std::string commandName = args[0];
	if(!commandMgr.CommandExists(commandName))
	{
		PrintIncorrectUsage(commandName);
		return -1;
	}

	// Parse existing tasks?
	CTU::TaskList taskList;
	if(commandMgr.CommandRequiresParse(commandName))
	{
		std::string taskListPath = pConfigFile->Get<std::string>(JK_CURRENT_TASK_LIST);
		std::string bullet = pConfigFile->Get<std::string>(JK_BULLET);
	}

	// Run command
	CTU::Command::ArgList cargs(args.begin() + 1, args.end());
	return commandMgr.Execute(commandName, cargs, taskList)? 0 : -1;
}