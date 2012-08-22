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
					       std::string("list the tasks within the active task list\r\n") +
					       std::string("note: tasks are listed in the order which they appear in-file\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return !args.size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					taskList.PrintNumeric();
					return true;
				}
		};
	}
}