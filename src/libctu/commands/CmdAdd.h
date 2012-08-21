#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"

namespace CTU
{
	namespace Commands
	{
		class CmdAdd : public CTU::Command
		{
			public:
				CmdAdd() { SetFlag(ECommandFlag::REQUIRES_TASK_LIST_SAVE); }

				virtual std::string GetName() const    { return "add"; }
				virtual std::string GetSummary() const { return "add a new task to the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu add \"ENTRY\"\r\n\r\n") +
					       std::string("add the specified entry to the active command list\r\n") +
					       std::string("note: quotes may be omited if the entry does not contain spaces\r\n") +
					       std::string("      to nest quotes use single quotes '' or escaped double quotes \\\"\r\n") +
					       std::string("      empty entries are classed as incorrect usage\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return (args.size() == 1) && args[0].size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					taskList.AddTask(args[0]);
					return true;
				}
		};
	}
}