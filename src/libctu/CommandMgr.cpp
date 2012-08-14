#include "CommandMgr.h"
#include "Utils.h"
#include <assert.h>

bool CTU::CommandMgr::CommandExists(const std::string& commandName) const
{
	return m_commands.find(commandName) != m_commands.end();
}

bool CTU::CommandMgr::CommandRequiresParse(const std::string& commandName)
{
	if(!CommandExists(commandName))
		return false;
	Command::Instance pCommand = m_commands[commandName];
	return pCommand->RequiresTaskListParse();
}

bool CTU::CommandMgr::CommandRequiresSave(const std::string& commandName)
{
	if(!CommandExists(commandName))
		return false;
	Command::Instance pCommand = m_commands[commandName];
	return pCommand->RequiresTaskListSave();
}

bool CTU::CommandMgr::Execute(const std::string& commandName, const CTU::Command::ArgList& args,
                              CTU::TaskList& taskList)
{
	if(!CommandExists(commandName))
		return false;

	Command::Instance pCommand = m_commands[commandName];
	if(!pCommand->Validate(args))
	{
		Utils::PrintLine(Utils::EColour::RED, "ERROR: Incorrect usage...\r\n");
		Utils::PrintLine("%s", pCommand->GetUsage().c_str());
		return false;
	}

	if(CommandRequiresParse(commandName) ||
	   CommandRequiresSave(commandName))
	{
		taskList.Parse();
	}

	if(!pCommand->Execute(args, taskList))
		return false;

	return pCommand->RequiresTaskListSave()? taskList.Save() : true;
}

void CTU::CommandMgr::PrintCommandSummaries() const
{
	static const u32 uAlignment = 12;
	std::string commandName;
	u32 commandNameLen;

	CommandMap::const_iterator i = m_commands.begin();
	for(; i != m_commands.end(); ++i)
	{
		commandName = i->first;
		commandNameLen = commandName.size();
		Utils::Print(" %s", commandName.c_str());
		for(u32 pos = 0; pos < (uAlignment - commandNameLen); ++pos)
			Utils::Print(" ");
		Utils::Print("%s", i->second->GetSummary().c_str());
	}
	Utils::PrintLine("");
}