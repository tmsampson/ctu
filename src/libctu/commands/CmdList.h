#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"

namespace CTU
{
	namespace Commands
	{
		class CmdList : public CTU::Command
		{
			public:
				virtual std::string GetName() const    { return "list"; }
				virtual std::string GetSummary() const { return "list tasks within the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu list\r\n\r\n") +
					       std::string("list the tasks within the active command list\r\n") +
					       std::string("note: tasks are listed in the order which they appear in-file\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return !args.size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList) const
				{
					if(!taskList.GetTaskCount())
					{
						Utils::PrintLine(Utils::EColour::YELLOW, "active task list is empty");
						return true;
					}

					u32 uLine = 1;
					const std::vector<CTU::Task>& allTasks = taskList.GetAllTasks();
					std::vector<CTU::Task>::const_iterator i = allTasks.begin();
					for(; i != allTasks.end(); ++i)
					{
						Utils::PrintLine("%d. %s", uLine, i->Contents.c_str());
						++uLine;
					}
					return true;
				}
		};
	}
}