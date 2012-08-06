#include <stdio.h>
#include "Utils.h"

int main(int argc, char* argv[])
{
	printf("result = %s", Utils::GetExecutableDir().c_str());
	return 1;
}
