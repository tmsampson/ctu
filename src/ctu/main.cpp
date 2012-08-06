#include <stdio.h>
#include "Utils.h"
#include "JSONFile.h"

namespace ctu
{
	const std::string JK_CURRENT_TASK_LIST = "currentTaskList";
	const std::string JK_VERBOSE = "verbose";

	bool RunStartupChecks(JSONFile& configFile)
	{
		// Ensure values are set OR default
		configFile.Set<bool>(JK_VERBOSE, configFile.Get<bool>(JK_VERBOSE, false));
		configFile.Save();

		// Get path to current task list
		std::string taskListPath = configFile.Get<std::string>(ctu::JK_CURRENT_TASK_LIST);

		// Is the current task list set?
		if(taskListPath.empty())
		{
			Utils::PrintLine("WARNING: No task list is currently set.");

			do
			{
				Utils::PrintLine("Where would you like your task list to be created? (leave blank for default)");
				Utils::Print("Task List Path: ");
				std::getline(std::cin, taskListPath);

				if(!taskListPath.empty())
				{
					if(!Utils::DirectoryExists(taskListPath))
						Utils::PrintLine("ERROR: The directory specified does not exist, please try again");
					continue;
				}

				taskListPath = Utils::GetDefaultTaskListDirectory();
			}
			while(!Utils::DirectoryExists(taskListPath));

			taskListPath = taskListPath + Utils::PATH_SEPARATOR + "tasks.txt";
			Utils::Print("Creating %s    ", taskListPath.c_str());
			if(!Utils::TouchFile(taskListPath))
			{
				Utils::PrintLine("FAIL");
				return false;
			}

			Utils::PrintLine("SUCCESS\r\n");
			configFile.Set<std::string>(ctu::JK_CURRENT_TASK_LIST, taskListPath);
		}

		return true;
	}
}

int main(int argc, char* argv[])
{
	JSONFile configFile(Utils::GetConfigFilePath());
	ctu::RunStartupChecks(configFile);
	return 0;
}
