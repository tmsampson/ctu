#ifndef CTU_H_
#define CTU_H_

#include "JSONFile.h"

namespace CTU
{
	bool RunStartupChecks(JSONFile& configFile);
	bool Begin(const std::vector<std::string>& args);
}

#endif