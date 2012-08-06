#ifndef T_UTILS_H_
#define T_UTILS_H_

#include "Utils.h"
#include <gtest/gtest.h>
#include "Common.h"
#include <fstream>

class TUtils : public ::testing::Test { };
static const char*  TEMP_FILE          = "ctutest_resources/temp";
static const char*  FS_TEST_FILE1      = "ctutest_resources/fs1";
static const char*  FS_TEST_FILE2      = "ctutest_resources/fs2";
static const char*  FS_TEST_FILE3      = "ctutest_resources/fs3";

// ************************************************
//  Utils::GetCurrentDir Tests
// ************************************************
TEST_F(TUtils, GetCurrentDir_NormalCall_ReturnNonEmptyString)
{
	ASSERT_TRUE(Utils::GetCurrentDir().size() > 0);
}

// ************************************************
//  Utils::GetExecutableDir Tests
// ************************************************
TEST_F(TUtils, GetExecutableDir_NormalCall_ReturnCurrentDir)
{
	// Note: When unit tests execute, executable directory
	//       should be same as working directory
	ASSERT_EQ(Utils::GetCurrentDir(), Utils::GetExecutableDir());
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
	ASSERT_TRUE(Utils::FileExists(EXISTING_FILE));
}

// ************************************************
//  Utils::GetFileSize Tests
// ************************************************
TEST_F(TUtils, GetFileSize_PassEmptyString_Return0)
{
	ASSERT_EQ(-1, Utils::GetFileSize(""));
}

TEST_F(TUtils, GetFileSize_PassBadFilename_Return0)
{
	ASSERT_EQ(-1, Utils::GetFileSize(BAD_FILENAME));
}

TEST_F(TUtils, GetFileSize_TestFile1_Return64)
{
	ASSERT_EQ(64, Utils::GetFileSize(FS_TEST_FILE1));
}

TEST_F(TUtils, GetFileSize_TestFile2_Return128)
{
	ASSERT_EQ(128, Utils::GetFileSize(FS_TEST_FILE2));
}

TEST_F(TUtils, GetFileSize_TestFile3_Return1024)
{
	ASSERT_EQ(1024, Utils::GetFileSize(FS_TEST_FILE3));
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