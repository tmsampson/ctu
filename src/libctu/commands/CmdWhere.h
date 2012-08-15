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
				CmdWhere() { ResetFlag(ECommandFlag::REQUIRES_PARSE); }

				virtual std::string GetName() const    { return "where"; }
				virtual std::string GetSummary() const { return "display the location of the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu where \r\n\r\n") +
					       std::string("display the location of the active task list\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return args.size() == 0;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList) const
				{
					Utils::PrintLine("Current task list stored at: %s", taskList.GetPath().c_str());
					return true;
				}
		};
		
	}
}