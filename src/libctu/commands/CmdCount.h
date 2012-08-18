#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"

namespace CTU
{
	namespace Commands
	{
		class CmdCount : public CTU::Command
		{
			public:
				virtual std::string GetName() const    { return "count"; }
				virtual std::string GetSummary() const { return "outputs the number of tasks in the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu count\r\n\r\n") +
					       std::string("outputs the number of tasks in the active task list\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return args.size() == 0;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					Utils::PrintLine("number of tasks in the active task list is: %i", taskList.GetTaskCount());
					return true;
				}
		};
	}
}