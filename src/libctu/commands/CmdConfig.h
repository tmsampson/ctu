#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"
#include <stdlib.h>
extern ConfigFile* pConfigFile;
extern const std::string JK_EDITOR;

namespace CTU
{
	namespace Commands
	{
		class CmdConfig : public CTU::Command
		{
			public:
				virtual std::string GetName() const    { return "config"; }
				virtual std::string GetSummary() const { return "opens ctu.settings file for editing"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu config\r\n\r\n") +
					       std::string("opens ctu.settings file for editing\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return args.size() == 0;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					std::string command = pConfigFile->Get<std::string>(JK_EDITOR) +
					                      " \"" + pConfigFile->GetPath() + "\"";
					system(command.c_str());
					return true;
				}
		};
	}
}