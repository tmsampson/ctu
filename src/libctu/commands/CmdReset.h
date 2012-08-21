#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"
extern ConfigFile* pConfigFile;

namespace CTU
{
	namespace Commands
	{
		class CmdReset : public CTU::Command
		{
			public:
				CmdReset() { ResetFlag(ECommandFlag::REQUIRES_TASK_LIST); }

				virtual std::string GetName() const    { return "reset"; }
				virtual std::string GetSummary() const { return "reset all settings to first-run defaults"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu reset\r\n\r\n") +
					       std::string("reset all ctu configuration settings (ctu.settings) to\r\n") +
					       std::string("their default values\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return !args.size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					if(!Utils::PromptYesNo("are you sure you wish to reset all settings?"))
					{
						Utils::PrintLine("settings will remain unchanged");
						return true;
					}

					pConfigFile->Clear();
					if(!CTU::ValidateConfigFile(pConfigFile))
						return false;
					return CTU::LocateTaskList(pConfigFile);
				}
		};
	}
}