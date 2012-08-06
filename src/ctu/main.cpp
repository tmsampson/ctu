#include <stdio.h>
#include "Utils.h"

int main(int argc, char* argv[])
{
	printf("result = %s\r\n", Utils::GetExecutableDir().c_str());
	return 1;
}
