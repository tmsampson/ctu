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
				virtual bool RequiresTaskListSave() const { return true; }
				virtual std::string GetName() const    { return "add"; }
				virtual std::string GetSummary() const { return "add a new task to the active task list"; }
				virtual std::string GetUsage() const
				{
					return "usage";
				}

				virtual bool Validate(const CTU::Command::ArgList& args)
				{
					return args.size() == 1;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					taskList.AddTask(args[0]);
					return true;
				}
		};
		
	}
}