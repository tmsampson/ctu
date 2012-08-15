#ifndef COMMAND_MGR_H_
#define COMMAND_MGR_H_

#include "Utils.h"
#include "TaskList.h"
#include "ConfigFile.h"
#include <vector>
#include <string>
#include <map>

namespace CTU
{
	class Command
	{
		public:
			typedef SharedPtr<CTU::Command> Instance;
			typedef std::vector<std::string> ArgList;

			virtual bool Validate(const ArgList& args) const = 0;
			virtual bool Execute(const ArgList& args, CTU::TaskList& taskList) const = 0;
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
			bool CommandRequiresParse(const std::string& commandName) const;
			bool CommandRequiresSave(const std::string& commandName) const;
			bool Execute(const std::string& commandName, const CTU::Command::ArgList& args,
			             CTU::TaskList& taskList) const;
			void PrintBasicCommandsSummary() const;
			void DisplayUsage(const std::string& commandName) const;

		private:
			typedef std::map<std::string, Command::Instance> CommandMap;
			Command::Instance GetCommandInstance(const std::string& commandName) const;
			CommandMap m_commands;
	};
}

#endif
