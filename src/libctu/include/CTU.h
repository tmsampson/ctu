#ifndef CTU_H_
#define CTU_H_

#include "ConfigFile.h"

namespace CTU
{
	bool RunStartupChecks(ConfigFile& configFile);
	bool Begin(const std::vector<std::string>& args);
}

#endif