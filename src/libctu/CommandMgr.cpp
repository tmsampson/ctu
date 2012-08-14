#include "CommandMgr.h"
#include "Utils.h"

bool CTU::CommandMgr::CommandExists(const std::string& name) const
{
	return m_commands.find(name) != m_commands.end();
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

bool CTU::CommandMgr::Execute(const std::string& commandName, const CTU::Command::ArgList& args)
{
	if(!CommandExists(commandName))
		return false;

	Command::Instance pCommand = m_commands[commandName];
	return pCommand->Execute(args);
}