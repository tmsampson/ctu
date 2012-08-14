#include "CTU.h"
#include "CommandMgr.h"
#include "Utils.h"
#include <string>
#include <map>

// CTU Commands
#include "commands/CmdAdd.h" // add

static CTU::CommandMgr commandMgr;
static const std::string JK_CURRENT_TASK_LIST = "currentTaskList";
static const std::string JK_VERBOSE           = "verbose";

bool CTU::RunStartupChecks(JSONFile& configFile)
{
	// Ensure values are set OR default
	configFile.Set<bool>(JK_VERBOSE, configFile.Get<bool>(JK_VERBOSE, false));
	configFile.Save();

	// Get path to current task list
	std::string taskListPath = configFile.Get<std::string>(JK_CURRENT_TASK_LIST);

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
	configFile.Set<std::string>(JK_CURRENT_TASK_LIST, taskListPath);

	return true;
}

void PrintIncorrectUsage(const std::string& commandName = "")
{
	Utils::PrintLine(Utils::EColour::RED, "Incorrect Usage!");
	if(commandName.size())
		Utils::PrintLine(Utils::EColour::RED, "ERROR: Command '%s' does not exist", commandName.c_str());
	commandMgr.PrintCommandSummaries();
}

bool CTU::Begin(const std::vector<std::string>& args)
{
	if(!args.size())
	{
		PrintIncorrectUsage();
		return false;
	}

	// Register all commands
	commandMgr.RegisterCommand<CTU::Commands::CmdAdd>(); // add

	// Does command exist?
	std::string commandName = args[0];
	if(!commandMgr.CommandExists(commandName))
	{
		PrintIncorrectUsage(commandName);
		return false;
	}

	// Run command
	CTU::Command::ArgList cargs(args.begin() + 1, args.end());
	return commandMgr.Execute(commandName, cargs);
}