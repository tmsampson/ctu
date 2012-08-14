#include "CTU.h"
#include "Utils.h"
#include "JSONFile.h"
#include "CommandMgr.h"
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
	JSONFile configFile(Utils::GetConfigFilePath());
	CTU::RunStartupChecks(configFile);

	// Collect all but first arg (process name)
	CTU::Command::ArgList args;
	for(s32 i = 1; i < argc; ++i)
		args.push_back(argv[i]);

	CTU::Begin(args);
	return 0;
}
