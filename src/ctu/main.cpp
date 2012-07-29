#include <stdio.h>
#include "Dummy.h"
#include "PropertiesFile.h"

int main(int argc, char* argv[])
{
	printf("10 + 2 = %d\r\n", add<int>(10, 2));
	PropertiesFile props("C://props.json");
	return 1;
}
