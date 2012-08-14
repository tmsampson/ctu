#include "CommandMgr.h"
extern CTU::CommandMgr commandMgr;

namespace CTU
{
	namespace Commands
	{
		class CmdHelp : public CTU::Command
		{
			public:
				virtual bool RequiresTaskListParse() const { return false; }
				virtual std::string GetName() const    { return "help"; }
				virtual std::string GetSummary() const { return "display usage instructions for a given command"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu help [COMMAND]\r\n\r\n") +
					       std::string("display detailed usage information for the specified command\r\n") +
					       std::string("note: if COMMAND is omited the basic commands summary is displayed\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args)
				{
					return args.size() <= 1;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					if(!args.size())
					{
						commandMgr.PrintBasicCommandsSummary();
						return true;
					}

					std::string commandName = args[0];
					if(!commandMgr.CommandExists(args[0]))
					{
						Utils::PrintLine(Utils::EColour::RED, "ERROR: Command '%s' does not exist", commandName);
						return false;
					}

					commandMgr.DisplayUsage(commandName);
					return true;
				}
		};
	}
}