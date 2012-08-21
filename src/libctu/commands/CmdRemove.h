#include "CTU.h"
#include "Utils.h"
#include "CommandMgr.h"
#include <algorithm>

namespace CTU
{
	namespace Commands
	{
		class CmdRemove : public CTU::Command
		{
			public:
				CmdRemove() : m_nTaskIndex(0) { SetFlag(ECommandFlag::REQUIRES_TASK_LIST_SAVE); }

				virtual std::string GetName() const    { return "remove"; }
				virtual std::string GetSummary() const { return "remove a task from the active task list"; }
				virtual std::string GetUsage() const
				{
					return std::string("ctu remove [-t TASK_NUMBER]\r\n\r\n") +
					       std::string("removes a single task from the active task list\r\n\r\n") +
					       std::string("options:\r\n") +
					       std::string(" -t        the numeric index of the task to be removed\r\n\r\n") +
					       std::string("note: if the -t option is omited, a prompt will allow a task\r\n") +
					       std::string("      to be selected manually for removal\r\n");
				}

				virtual bool Validate(const CTU::Command::ArgList& args) const
				{
					if(!args.size())
						return true;

					if(args[0] != "-t" || args.size() != 2)
						return false;

					if(args[1] == "0")
						return true;

					m_nTaskIndex = atoi(args[1].c_str());
					return m_nTaskIndex != 0;
				}

				virtual bool Execute(const CTU::Command::ArgList& args, CTU::TaskList& taskList)
				{
					// Is task list empty?
					if(!taskList.GetTaskCount())
					{
						Utils::PrintLine(Utils::EColour::YELLOW, "active task list is empty");
						return false;
					}

					// Was task index passed as arg? If not prompt
					if(!m_nTaskIndex)
					{
						bool bUserCancelled = false;
						m_nTaskIndex = Utils::PromptTaskIndex(taskList, bUserCancelled);
						if(bUserCancelled)
						{
							Utils::PrintLine("no tasks were removed");
							return false;
						}
					}

					// Attempt to remove task
					std::string removedItem;
					if(m_nTaskIndex <=0 || !taskList.RemoveTask(m_nTaskIndex, removedItem))
					{
						Utils::PrintLine(Utils::EColour::RED, "ERROR: invalid task index");
						return false;
					}

					// Inform user of removed task
					static const u32 uTruncateMaxLength = 30;
					std::string truncatedItemText = Utils::StringTruncate(removedItem, uTruncateMaxLength);
					Utils::PrintLine(Utils::EColour::GREEN,
					                 "task (%d. %s%s) was removed\r\n",
					                 m_nTaskIndex,
					                 truncatedItemText.c_str(),
					                 (removedItem.size() > uTruncateMaxLength)? "..." : "");
					return true;
				}

			private:
				mutable s32 m_nTaskIndex;
		};
	}
}