#include <stdio.h>
#include "Utils.h"
#include "JSONFile.h"
#include "CTU.h"

int main(int argc, char* argv[])
{
	JSONFile configFile(Utils::GetConfigFilePath());
	CTU::RunStartupChecks(configFile);
	return 0;
}
