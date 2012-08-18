#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"

namespace CTU
{
	namespace Commands
	{
		class CmdClear : public CTU::Command
		{
			public:
				virtual std::string GetName() const    { return "clear"; }
				virtual std::string GetSummary() const { return "remove all tasks from the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu clear\r\n\r\n") +
					       std::string("remove all tasks from the current task list\r\n") +
					       std::string("note: this operation cannot be undone\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					return !args.size();
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					if(!taskList.GetTaskCount())
					{
						Utils::PrintLine(Utils::EColour::YELLOW, "active task list is empty");
						return false;
					}

					if(!Utils::PromptYesNo("are you sure you wish to clear the active task list?"))
					{
						Utils::PrintLine("active task list was not cleared");
						return true;
					}

					taskList.Clear();
					SetFlag(ECommandFlag::REQUIRES_SAVE);
					return true;
				}
		};
	}
}