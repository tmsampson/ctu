#ifndef CTU_H_
#define CTU_H_

#include "ConfigFile.h"

namespace CTU
{
	bool RunStartupChecks(ConfigFile* pCconfig);
	int Begin(const std::vector<std::string>& args);
}

#endif