#include <gtest/gtest.h>

// Tests
#include "tests/TUtils.h"
#include "tests/TConfigFile.h"
#include "tests/TTaskList.h"

const char*  EMPTY_STRING            = "";
const char*  BAD_PATH                = "<>|,.../";
const char*  BAD_FILENAME            = BAD_PATH;
const char*  NONE_EXISTENT_FILE      = "ctutest_resources/none-existent-file";
const char*  NONE_EXISTENT_DIRECTORY = "ctutest_resources/none-existent-dir";
const char*  EXISTING_FILE           = "ctutest_resources/existing-file";

int main(int argc, char* argv[])
{
	Utils::SuppressPrint(); // Silence stdout

	// Initialise and run tests
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
