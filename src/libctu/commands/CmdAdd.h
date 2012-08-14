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
				virtual std::string GetName() const    { return "add"; }
				virtual std::string GetSummary() const { return "add a new task to the active task list"; }
				virtual std::string GetUsage() const
				{
					return "usage";
				}

				virtual bool Execute(const CTU::Command::ArgList& args)
				{
					Utils::PrintLine("I am the add command :)");
					return true;
				}
		};
		
	}
}