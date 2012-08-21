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
	namespace ECommandFlag
	{
		enum Enum
		{
			REQUIRES_TASK_LIST      = 1 << 0,
			REQUIRES_TASK_LIST_SAVE = 1 << 1,
		};
	}

	class Command
	{
		public:
			typedef SharedPtr<CTU::Command> Instance;
			typedef std::vector<std::string> ArgList;

			Command();
			virtual bool Validate(const ArgList& args) const = 0;
			virtual bool Execute(const ArgList& args, CTU::TaskList& taskList) = 0;
			virtual std::string GetName() const = 0;
			virtual std::string GetSummary() const = 0;
			virtual std::string GetUsage() const = 0;
			bool FlagIsSet(ECommandFlag::Enum flag) const;
			void SetFlag(ECommandFlag::Enum flag);
			void ResetFlag(ECommandFlag::Enum flag);

		private:
			u32 m_uFlags;
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
			bool CommandExists(std::string& commandName) const;
			bool CommandRequiresTaskList(const std::string& commandName) const;
			bool CommandRequiresTaskListSave(const std::string& commandName) const;
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
