#include <stdio.h>
#include "Utils.h"
#include "JSONFile.h"

namespace ctu
{
	const std::string JK_CURRENT_TASK_LIST = "currentTaskList";
	const std::string JK_VERBOSE = "verbose";

	bool RunStartupChecks(JSONFile& configFile)
	{
		// Get path to current task list
		std::string taskListPath = configFile.Get<std::string>(ctu::JK_CURRENT_TASK_LIST);

		// Is the current task list set?
		if(taskListPath.empty())
		{
			printf("WARNING: No task list is currently set.\r\n");

			do
			{
				printf("Where would you like your task list to be created? (leave blank for default)\r\n");
				printf("Task List Path: ");
				std::getline(std::cin, taskListPath);

				if(!taskListPath.empty())
				{
					if(!Utils::DirectoryExists(taskListPath))
						printf("ERROR: The directory specified does not exist, please try again\r\n");
					continue;
				}

				taskListPath = Utils::GetDefaultTaskListDirectory();
			}
			while(!Utils::DirectoryExists(taskListPath));

			taskListPath = taskListPath + Utils::PATH_SEPARATOR + "tasks.txt";
			configFile.Set<std::string>(ctu::JK_CURRENT_TASK_LIST, taskListPath);
			printf("Creating %s    ", taskListPath.c_str());
		}

		// Ensure values are set OR default
		configFile.Set<bool>(JK_VERBOSE, configFile.Get<bool>(JK_VERBOSE, false));

		configFile.Save();
		return true;
	}
}

int main(int argc, char* argv[])
{
	JSONFile configFile(Utils::GetConfigFilePath());
	ctu::RunStartupChecks(configFile);
	return 0;
}
