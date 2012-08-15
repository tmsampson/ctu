#ifndef T_UTILS_H_
#define T_UTILS_H_

#include "Utils.h"
#include "Common.h"
#include <gtest/gtest.h>
#include <fstream>

class TUtils : public ::testing::Test { };
static const char*  TEMP_FILE          = "ctutest_resources/temp";
static const char*  FS_TEST_FILE1      = "ctutest_resources/fs1";
static const char*  FS_TEST_FILE2      = "ctutest_resources/fs2";
static const char*  FS_TEST_FILE3      = "ctutest_resources/fs3";
static const char*  TOUCH_FILE         = "ctutest_resources/touch";

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

TEST_F(TUtils, FileExists_PassNoneExistenDir_ReturnFalse)
{
	ASSERT_FALSE(Utils::FileExists(NONE_EXISTENT_DIRECTORY));
}

TEST_F(TUtils, FileExists_PassExistingDir_ReturnFalse)
{
	// Note: On Linux/Unix directories CAN legitimately
	//       be opened as files
	#if defined(_WIN32)
	ASSERT_FALSE(Utils::FileExists(Utils::GetCurrentDir()));
	#endif
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
//  Utils::TouchFile Tests
// ************************************************
TEST_F(TUtils, TouchFile_PassEmptyString_ReturnFalse)
{
	ASSERT_FALSE(Utils::TouchFile(""));
}

TEST_F(TUtils, TouchFile_PassBadFilename_ReturnFalse)
{
	ASSERT_FALSE(Utils::TouchFile(BAD_FILENAME));
}

TEST_F(TUtils, TouchFile_PassDirectory_PerPlatformBehaviour)
{
	// Note: On Linux/Unix it is valid to perform a touch
	//       on an existing directory
	#if defined(_WIN32)
	ASSERT_FALSE(Utils::TouchFile(Utils::GetCurrentDir()));
	#else
	ASSERT_TRUE(Utils::TouchFile(Utils::GetCurrentDir()));
	#endif
}

TEST_F(TUtils, TouchFile_FileExists_ReturnTrue)
{
	ASSERT_TRUE(Utils::TouchFile(EXISTING_FILE));
}

TEST_F(TUtils, TouchFile_FileDoesNotExist_ReturnTrue)
{
	ASSERT_TRUE(Utils::TouchFile(TOUCH_FILE));
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

TEST_F(TUtils, DirectoryExists_PassNoneExistentDir_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(NONE_EXISTENT_DIRECTORY));
}

TEST_F(TUtils, DirectoryExists_PassNoneExistentFile_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(NONE_EXISTENT_FILE));
}

TEST_F(TUtils, DirectoryExists_PassExistingFile_ReturnFalse)
{
	ASSERT_FALSE(Utils::DirectoryExists(EXISTING_FILE));
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

// ************************************************
//  Utils::StringTrim Tests
// ************************************************
TEST_F(TUtils, StringTrim_NoWhiteSpacePresent_StringUnchanged)
{
	std::string str = "Hello World!";
	std::string trimmedStr = Utils::StringTrim(str);
	ASSERT_EQ(str, trimmedStr);
}

TEST_F(TUtils, StringTrim_WhiteSpacePresent_WhiteSpaceStripped)
{
	std::string trimmedStr = Utils::StringTrim("Hello World!   ");
	ASSERT_EQ("Hello World!", trimmedStr);
}

TEST_F(TUtils, StringTrim_EmptyStringPassed_StringUnchanged)
{
	std::string str = "";
	std::string trimmedStr = Utils::StringTrim(str);
	ASSERT_EQ(str, trimmedStr);
}

TEST_F(TUtils, StringTrim_OnlyWhiteSpacePresent_ReturnsEmptyString)
{
	std::string trimmedStr = Utils::StringTrim("   ");
	ASSERT_EQ("", trimmedStr);
}

TEST_F(TUtils, StringTrim_EmptyTrimChars_StringUnchanged)
{
	std::string str = "Hello World!";
	std::string trimChars = "";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ(str, trimmedStr);
}

TEST_F(TUtils, StringTrim_EmptyStringWithTrimChars_ReturnsEmptyString)
{
	std::string str = "";
	std::string trimChars = "! ";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ(str, trimmedStr);
}

TEST_F(TUtils, StringTrim_WhiteSpaceTrimChar_WhiteSpaceTrimmed)
{
	std::string str = "Hello World!   ";
	std::string trimChars = " ";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("Hello World!", trimmedStr);
}

TEST_F(TUtils, StringTrim_MultipleTrimCharsInLogicalOrder_CharsTrimmed)
{
	std::string str = "Hello World!   ";
	std::string trimChars = "! ";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("Hello World", trimmedStr);
}

TEST_F(TUtils, StringTrim_MultipleTrimCharsInReverseOrder_CharsTrimmed)
{
	std::string str = "Hello World!   ";
	std::string trimChars = " !";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("Hello World", trimmedStr);
}

TEST_F(TUtils, StringTrim_ManyTrimChars_CharsTrimmed)
{
	std::string str = "Hello World!](   )[";
	std::string trimChars = " !()[]";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("Hello World", trimmedStr);
}

TEST_F(TUtils, StringTrim_PassFwddSlash_FwdSlashTrimmed)
{
	std::string str = "C:/";
	std::string trimChars = "/";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("C:", trimmedStr);
}

TEST_F(TUtils, StringTrim_PassFwdSlashAndPeriod_BothTrimmed)
{
	std::string str = "C:/../";
	std::string trimChars = "./";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("C:", trimmedStr);
}

TEST_F(TUtils, StringTrim_PassFwdAndBackSlashAndPeriod_AllThreeTrimmed)
{
	std::string str = "C:\\/../";
	std::string trimChars = ".\\/";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("C:", trimmedStr);
}

TEST_F(TUtils, StringTrim_StringContainsOnlyTrimChars_EntireStringTrimmed)
{
	std::string str = "*&^";
	std::string trimChars = "*&^";
	std::string trimmedStr = Utils::StringTrim(str, trimChars);
	ASSERT_EQ("", trimmedStr);
}

// ************************************************
//  Utils::StringToLower Tests
// ************************************************
TEST_F(TUtils, StringToLower_PassEmptyString_ReturnEmptyString)
{
	std::string str = "";
	ASSERT_EQ(str, Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassLowerCaseString_StringUnchanged)
{
	std::string str = "hello";
	ASSERT_EQ(str, Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassUpperCaseString_ReturnAllLowerCaseString)
{
	std::string str = "SHRUNK";
	ASSERT_EQ("shrunk", Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassMixedCaseString_ReturnAllLowerCaseString)
{
	std::string str = "CaMeL";
	ASSERT_EQ("camel", Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassLowerCaseStringMixedChars_StringUnchanged)
{
	std::string str = "hello!_@@~# world";
	ASSERT_EQ(str, Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassUpperCaseStringMixedChars_ReturnAllLowerCaseString)
{
	std::string str = "HELLO!_@@~# WORLD";
	ASSERT_EQ("hello!_@@~# world", Utils::StringToLower(str));
}

TEST_F(TUtils, StringToLower_PassMixedCaseStringMixedChars_ReturnAllLowerCaseString)
{
	std::string str = "CaMeL!_@@~# CaSe";
	ASSERT_EQ("camel!_@@~# case", Utils::StringToLower(str));
}
#endif