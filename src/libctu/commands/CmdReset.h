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
				CmdReset() { ResetFlag(ECommandFlag::REQUIRES_PARSE); }

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

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList) const
				{
					std::string result;
					bool bValidResult = false;
					while(!bValidResult)
					{
						Utils::PrintLine(Utils::EColour::YELLOW, "are you sure you wish to reset all settings? (y/n): ");
						std::getline(std::cin, result);
						bValidResult = (result == "y"   || result == "n" ||
						                result == "yes" || result == "no");
					}

					if(result[0] == 'n')
					{
						Utils::PrintLine("settings will remain unchanged");
						return true;
					}

					pConfigFile->Clear();
					return CTU::RunStartupChecks(pConfigFile);
				}
		};
	}
}