#include "CommandMgr.h"
#include "Utils.h"

bool CTU::CommandMgr::CommandExists(const std::string& name) const
{
	return m_commands.find(name) != m_commands.end();
}

void CTU::CommandMgr::PrintCommandSummaries() const
{
	CommandMap::const_iterator i = m_commands.begin();
	for(; i != m_commands.end(); ++i)
		Utils::Print("%s    %s", i->first.c_str(), i->second->GetSummary().c_str());
}

bool CTU::CommandMgr::Execute(const std::string& commandName, const CTU::Command::ArgList& args)
{
	if(!CommandExists(commandName))
		return false;

	SharedPtr<CTU::Command> pCommand = m_commands[commandName];
	return pCommand->Execute(args);
}