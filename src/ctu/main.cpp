#include "CTU.h"
#include "Utils.h"
#include "ConfigFile.h"
#include "CommandMgr.h"

int main(int argc, char* argv[])
{
	ConfigFile configFile(Utils::GetConfigFilePath());
	CTU::RunStartupChecks(&configFile);

	// Collect all but first arg (process name)
	CTU::Command::ArgList args;
	for(s32 i = 1; i < argc; ++i)
		args.push_back(argv[i]);

	return CTU::Begin(args);
}
