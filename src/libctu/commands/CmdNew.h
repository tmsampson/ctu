#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"
extern ConfigFile* pConfigFile;
extern const std::string JK_TASK_LIST_FILE;

namespace CTU
{
	namespace Commands
	{
		class CmdNew : public CTU::Command
		{
			public:
				CmdNew() { ResetFlag(ECommandFlag::REQUIRES_TASK_LIST); }

				virtual std::string GetName() const    { return "new"; }
				virtual std::string GetSummary() const { return "creates a new task list within the current directory"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu new\r\n\r\n") +
					       std::string("creates a new task list within the current directory\r\n") +
					       std::string("note: this does nothing more than create an empty task list\r\n") +
					       std::string("      within the current directory and does not modify the\r\n") +
					       std::string("      defaultTaskList value within ctu.settings, if a task list\r\n") +
					       std::string("      already exists within the current directory this will\r\n") +
					       std::string("      not be overwritten\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return !args.size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					std::string newTaskList = Utils::GetCurrentDir() +
					                          Utils::PATH_SEPARATOR +
					                          pConfigFile->Get<std::string>(JK_TASK_LIST_FILE);

					Utils::Print("creating %s    ", newTaskList.c_str());
					if(Utils::FileExists(newTaskList))
					{
						Utils::PrintLine(Utils::EColour::YELLOW, "EXISTS");
						return true;
					}

					if(!Utils::TouchFile(newTaskList))
					{
						Utils::PrintLine(Utils::EColour::RED, "FAIL");
						return false;
					}

					Utils::PrintLine(Utils::EColour::GREEN, "SUCCESS");
					return true;
				}
		};
	}
}