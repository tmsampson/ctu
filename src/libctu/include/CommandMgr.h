#ifndef COMMAND_MGR_H_
#define COMMAND_MGR_H_

#include <vector>
#include <string>
#include <map>
#include "Utils.h"
#include "TaskList.h"
#include "ConfigFile.h"

namespace CTU
{
	class Command
	{
		public:
			typedef SharedPtr<CTU::Command> Instance;
			typedef std::vector<std::string> ArgList;
			virtual bool Validate(const ArgList& args) = 0;
			virtual bool Execute(const ArgList& args, CTU::TaskList& taskList) = 0;
			virtual std::string GetName() const = 0;
			virtual std::string GetSummary() const = 0;
			virtual std::string GetUsage() const = 0;
			virtual bool RequiresTaskListParse() const { return true; }
			virtual bool RequiresTaskListSave() const { return false; }
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
			bool CommandRequiresSave(const std::string& commandName);
			bool Execute(const std::string& commandName, const CTU::Command::ArgList& args,
			             CTU::TaskList& taskList);
			void PrintBasicCommandsSummary() const;
			void DisplayUsage(const std::string& commandName);

		private:
			typedef std::map<std::string, Command::Instance> CommandMap;
			CommandMap m_commands;
	};
}

#endif
