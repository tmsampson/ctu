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
				virtual std::string GetSummary() const { return "summary"; }
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