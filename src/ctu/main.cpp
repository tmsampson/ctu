#include <stdio.h>
#include "dummy.h"

int main(int argc, char* argv[])
{
	printf("10 + 2 = %d\r\n", add<int>(10, 2));
	return 1;
}
