#include "CommandMgr.h"
#include "Utils.h"

CTU::Command::Command() : m_uFlags(0)
{
	SetFlag(ECommandFlag::REQUIRES_TASK_LIST);
}

bool CTU::Command::FlagIsSet(ECommandFlag::Enum flag) const
{
	return (m_uFlags & flag) != 0;
}

void CTU::Command::SetFlag(ECommandFlag::Enum flag)
{
	m_uFlags |= flag;
}

void CTU::Command::ResetFlag(ECommandFlag::Enum flag)
{
	m_uFlags &= ~flag;
}

bool CTU::CommandMgr::CommandExists(const std::string& commandName) const
{
	return (m_commands.find(commandName) != m_commands.end());
}

bool CTU::CommandMgr::CommandExists(std::string& commandName) const
{
	if(m_commands.find(commandName) != m_commands.end())
		return true;

	// Perhaps commandName is an abbreviation?
	std::string existingCommandName;
	CommandMap::const_iterator i = m_commands.begin();
	for(; i != m_commands.end(); ++i)
	{
		existingCommandName = i->second->GetName();
		if(existingCommandName.size() <= commandName.size())
			continue;
		if(existingCommandName.substr(0, commandName.size()) == commandName)
		{
			// Match found
			commandName = existingCommandName;
			return true;
		}
	}

	// No abbreviation matches
	return false;
}

bool CTU::CommandMgr::CommandRequiresTaskList(const std::string& commandName) const
{
	if(!CommandExists(commandName))
		return false;
	Command::Instance pCommand = GetCommandInstance(commandName);
	return pCommand->FlagIsSet(ECommandFlag::REQUIRES_TASK_LIST);
}

bool CTU::CommandMgr::CommandRequiresTaskListSave(const std::string& commandName) const
{
	if(!CommandExists(commandName))
		return false;
	Command::Instance pCommand = GetCommandInstance(commandName);
	return pCommand->FlagIsSet(ECommandFlag::REQUIRES_TASK_LIST_SAVE);
}

bool CTU::CommandMgr::Execute(const std::string& commandName, const CTU::Command::ArgList& args,
                              CTU::TaskList& taskList) const
{
	if(!CommandExists(commandName))
		return false;

	Command::Instance pCommand = GetCommandInstance(commandName);
	if(!pCommand->Validate(args))
	{
		Utils::PrintLine(Utils::EColour::RED, "ERROR: incorrect usage...\r\n");
		Utils::PrintLine("%s", pCommand->GetUsage().c_str());
		return false;
	}

	if(CommandRequiresTaskList(commandName) ||
	   CommandRequiresTaskListSave(commandName))
	{
		if(!taskList.Parse())
			return false;
	}

	if(!pCommand->Execute(args, taskList))
		return false;

	return CommandRequiresTaskListSave(commandName)? taskList.Save() : true;
}

void CTU::CommandMgr::PrintBasicCommandsSummary() const
{
	Utils::PrintLine("CTU Command-line Task Utility");
	Utils::PrintLine("\r\nbasic commands:\r\n");

	static const u32 uAlignment = 12;
	std::string commandName, commandSummary;
	u32 commandNameLen;

	CommandMap::const_iterator i = m_commands.begin();
	for(; i != m_commands.end(); ++i)
	{
		commandName    = Utils::StringToLower(i->first);
		commandSummary = Utils::StringToLower(i->second->GetSummary());
		commandNameLen = commandName.size();
		Utils::Print(" %s", commandName.c_str());
		for(u32 pos = 0; pos < (uAlignment - commandNameLen); ++pos)
			Utils::Print(" ");
		Utils::PrintLine("%s", commandSummary.c_str());
	}

	Utils::PrintLine("\r\n");
	Utils::PrintLine("use \"ctu help COMMAND\" for command specific usage details");
	Utils::PrintLine("");
}

void CTU::CommandMgr::DisplayUsage(const std::string& commandName) const
{
	if(!CommandExists(commandName))
		return;

	Command::Instance pCommand = GetCommandInstance(commandName);
	Utils::Print("%s", pCommand->GetUsage().c_str());
}

CTU::Command::Instance CTU::CommandMgr::GetCommandInstance(const std::string& commandName) const
{
	CTU_ASSERT(CommandExists(commandName), "Command did not exist");
	CommandMap::const_iterator result = m_commands.find(commandName);
	return result->second;
}
