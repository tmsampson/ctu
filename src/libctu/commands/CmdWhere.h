#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"

namespace CTU
{
	namespace Commands
	{
		class CmdWhere : public CTU::Command
		{
			public:
				virtual bool RequiresTaskListSave() const { return false; }
				virtual std::string GetName() const    { return "where"; }
				virtual std::string GetSummary() const { return "prints the location of the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu where \"ENTRY\"\r\n\r\n") +
					       std::string("prints the location of the active task list\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args)
				{
					return args.size() == 0;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					Utils::PrintLine("Current task list stored at: %s", taskList.Where().c_str());
					return true;
				}
		};
		
	}
}