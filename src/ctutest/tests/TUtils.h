#ifndef T_UTILS_H_
#define T_UTILS_H_

#include "Utils.h"
#include <gtest/gtest.h>
#include "Common.h"
#include <fstream>

class TUtils : public ::testing::Test { };
static const char*  TEMP_FILE = "ctutest_resources/temp";

// ************************************************
//  Utils::GetCurrentDir Tests
// ************************************************
TEST_F(TUtils, GetCurrentDir_NormalCall_ReturnNonEmptyString)
{
	ASSERT_TRUE(Utils::GetCurrentDir().size() > 0);
}

// ************************************************
//  Utils::FileExists Tests
// ************************************************
TEST_F(TUtils, FileExists_PassEmptyString_ReturnFalse)
{
	ASSERT_FALSE(Utils::FileExists(""));
}

TEST_F(TUtils, FileExists_PassBadFilename_ReturnFalse)
{
	ASSERT_FALSE(Utils::FileExists(BAD_FILENAME));
}

TEST_F(TUtils, FileExists_PassValidFile_ReturnTrue)
{
	std::ofstream temp(TEMP_FILE);
	ASSERT_TRUE(temp.is_open()); temp.close();
	ASSERT_TRUE(Utils::FileExists(TEMP_FILE));
}

// ************************************************
//  Utils::DirectoryExists Tests
// ************************************************
TEST_F(TUtils, DirectoryExists_PassEmptyString_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(""));
}

TEST_F(TUtils, DirectoryExists_PassBadPath_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(BAD_PATH));
}

TEST_F(TUtils, DirectoryExists_PassNoneExistenDir_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(NONE_EXISTENT_DIRECTORY));
}

TEST_F(TUtils, DirectoryExists_PassExistingDir_ReturnTrue)
{
	ASSERT_TRUE(Utils::DirectoryExists(Utils::GetCurrentDir()));
}

// ************************************************
//  Utils::GetDefaultTaskListDirectory Tests
// ************************************************
TEST_F(TUtils, GetDefaultTaskListDirectory_Call_ValidPathReturned)
{
	std::string path = Utils::GetDefaultTaskListDirectory();
	ASSERT_TRUE(Utils::DirectoryExists(path));
}

#endif