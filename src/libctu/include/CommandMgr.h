#ifndef COMMAND_MGR_H_
#define COMMAND_MGR_H_

#include <vector>
#include <string>
#include <map>
#include "Utils.h"
#include "TaskList.h"

namespace CTU
{
	class Command
	{
		public:
			typedef SharedPtr<CTU::Command> Instance;
			typedef std::vector<std::string> ArgList;
			virtual bool Execute(const ArgList& args, CTU::TaskList& taskList) = 0;
			virtual std::string GetName() const = 0;
			virtual std::string GetSummary() const = 0;
			virtual std::string GetUsage() const = 0;
			virtual bool RequiresTaskListParse() const { return true; }
	};

	class CommandMgr
	{
		public:

			template<typename T>
			bool RegisterCommand()
			{
				Command::Instance pCommand(new T());
				if(CommandExists(pCommand->GetName()))
					return false;
				m_commands.insert(std::make_pair(pCommand->GetName(), pCommand));
				return true;
			}

			bool CommandExists(const std::string& commandName) const;
			bool CommandRequiresParse(const std::string& commandName);
			bool Execute(const std::string& commandName, const CTU::Command::ArgList& args,
			             CTU::TaskList& taskList);
			void PrintCommandSummaries() const;

		private:
			typedef std::map<std::string, Command::Instance> CommandMap;
			CommandMap m_commands;
	};
}

#endif
