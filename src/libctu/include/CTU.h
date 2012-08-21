#ifndef CTU_H_
#define CTU_H_

#include "ConfigFile.h"

namespace CTU
{
	bool ValidateConfigFile(ConfigFile* pConfig);
	bool LocateTaskList(ConfigFile* pConfig);
	int  Begin(const std::vector<std::string>& args, ConfigFile* pConfig);
}

#endif