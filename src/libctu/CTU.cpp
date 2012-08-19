#include "CTU.h"
#include "CommandMgr.h"
#include "Utils.h"
#include "TaskList.h"
#include <string>
#include <map>
#include <iostream>

// CTU Commands
#include "commands/CmdAdd.h"    // add
#include "commands/CmdClear.h"  // clear
#include "commands/CmdConfig.h" // config
#include "commands/CmdCount.h"  // count
#include "commands/CmdHelp.h"   // help
#include "commands/CmdList.h"   // list
#include "commands/CmdRemove.h" // remove
#include "commands/CmdReset.h"  // reset
#include "commands/CmdWhere.h"  // where

ConfigFile* pConfigFile;
CTU::CommandMgr commandMgr;
static CTU::TaskList taskList;
const std::string defaultTaskListFile = "tasks.txt";
const std::string JK_MAIN_TASK_LIST   = "mainTaskList";
const std::string JK_TASK_LIST_FILE   = "tasklist";
const std::string JK_VERBOSE          = "verbose";
const std::string JK_BULLET           = "bullet";
const std::string JK_EDITOR           = "editor";

void PrintIncorrectUsage(const std::string& commandName = "")
{
	if(commandName.size())
		Utils::PrintLine(Utils::EColour::RED, "ctu: unknown command '%s'", commandName.c_str());
	commandMgr.PrintBasicCommandsSummary();
}

std::string SetupMainTaskList()
{
	std::string taskListPath;

	do
	{
		Utils::PrintLine("where would you like your task list to be created? (leave blank for current directory)");
		Utils::Print("task list path: ");
		std::getline(std::cin, taskListPath);

		if(!taskListPath.empty())
		{
			taskListPath = Utils::StringTrim(taskListPath, ".\\/");
			if(!Utils::DirectoryExists(taskListPath))
				Utils::PrintLine(Utils::EColour::RED, "ERROR: the directory specified does not exist, please try again");
			continue;
		}

		taskListPath = Utils::GetCurrentDir();
	}
	while(!Utils::DirectoryExists(taskListPath));

	taskListPath = taskListPath + Utils::PATH_SEPARATOR + pConfigFile->Get<std::string>(JK_TASK_LIST_FILE);
	Utils::Print("Creating %s    ", taskListPath.c_str());
	if(!Utils::TouchFile(taskListPath))
	{
		Utils::PrintLine(Utils::EColour::RED, "FAIL");
		return "";
	}

	pConfigFile->Set<std::string>(JK_MAIN_TASK_LIST, taskListPath);
	Utils::PrintLine(Utils::EColour::GREEN, "SUCCESS\r\n");
	return taskListPath;
}

bool CTU::RunStartupChecks(ConfigFile* pConfig)
{
	pConfigFile = pConfig;

	// Ensure values are set OR default
	pConfigFile->Set<bool>(JK_VERBOSE, pConfigFile->Get<bool>(JK_VERBOSE, false));
	pConfigFile->Set<std::string>(JK_BULLET, pConfigFile->Get<std::string>(JK_BULLET, "> "));
	pConfigFile->Set<std::string>(JK_EDITOR, pConfigFile->Get<std::string>(JK_EDITOR, Utils::GetDefaultEditor()));
	pConfigFile->Set<std::string>(JK_MAIN_TASK_LIST, pConfigFile->Get<std::string>(JK_MAIN_TASK_LIST, ""));
	pConfigFile->Set<std::string>(JK_TASK_LIST_FILE, pConfigFile->Get<std::string>(JK_TASK_LIST_FILE, defaultTaskListFile));

	// Handle any empty string values
	if(pConfigFile->Get<std::string>(JK_EDITOR) == "")
		pConfigFile->Set<std::string>(JK_EDITOR, Utils::GetDefaultEditor());
	if(pConfigFile->Get<std::string>(JK_TASK_LIST_FILE) == "")
		pConfigFile->Set<std::string>(JK_TASK_LIST_FILE, defaultTaskListFile);
	pConfigFile->Save();

	// 1. Is a "main" task list set?
	std::string taskListPath = pConfigFile->Get<std::string>(JK_MAIN_TASK_LIST);
	if(!taskListPath.size())
	{
		// 2. Recursively search up directory tree to find a task list
		bool bTaskListFound = Utils::SearchDirectoryTreeForFile(Utils::GetCurrentDir(),
		                                                        pConfigFile->Get<std::string>(JK_TASK_LIST_FILE),
		                                                        taskListPath);

		// 3. Final fallback - Ask the user where to create the main task list
		if(!bTaskListFound)
		{
			Utils::PrintLine(Utils::EColour::YELLOW, "WARNING: no task list is currently set");
			taskListPath = SetupMainTaskList();
			if(!taskListPath.size())
				return false;
		}
	}

	// Initialise TaskList object
	if(!taskList.Init(taskListPath, pConfigFile->Get<std::string>(JK_BULLET)))
	{
		Utils::PrintLine(Utils::EColour::RED, "ERROR: active task list was missing and could not be created");
		return false;
	}

	return true;
}

int CTU::Begin(const std::vector<std::string>& args)
{
	// Register all commands
	commandMgr.RegisterCommand<CTU::Commands::CmdAdd>();    // add
	commandMgr.RegisterCommand<CTU::Commands::CmdClear>();  // clear
	commandMgr.RegisterCommand<CTU::Commands::CmdConfig>(); // config
	commandMgr.RegisterCommand<CTU::Commands::CmdCount>();  // count
	commandMgr.RegisterCommand<CTU::Commands::CmdHelp>();   // help
	commandMgr.RegisterCommand<CTU::Commands::CmdList>();   // list
	commandMgr.RegisterCommand<CTU::Commands::CmdRemove>(); // remove
	commandMgr.RegisterCommand<CTU::Commands::CmdReset>();  // reset
	commandMgr.RegisterCommand<CTU::Commands::CmdWhere>();  // where

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

	CTU::Command::ArgList cargs(args.begin() + 1, args.end());
	return commandMgr.Execute(commandName, cargs, taskList)? 0 : -1;
}