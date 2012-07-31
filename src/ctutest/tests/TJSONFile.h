#ifndef T_JSONFILE_H_
#define T_JSONFILE_H_

#include <stdio.h>
#include <limits>
#include <gtest/gtest.h>
#include "JSONFile.h"
#include "BasicTypes.h"

class TJSONFile : public ::testing::Test { };
static const char* EMPTY_STRING            = "";
static const char* BAD_PATH                = "<>|,...";
static const char* NONE_EXISTENT_FILE      = "ctutest_resources/none-existent-file";
static const char* SAVE_NEW_FILE           = "ctutest_resources/save-new-file";
static const char* CREATE_NEW_FILE         = "ctutest_resources/create-new-file";
static const char* SCOPED_SAVE             = "ctutest_resources/scoped-save";
static const char* IS_LOADED_TEST1         = "ctutest_resources/is-loaded";
static const char* EXISTING_FILE           = "ctutest_resources/existing-file";
static const char* EXISTING_MALFORMED_FILE = "ctutest_resources/existing-malfomed-file";

// ************************************************
// JSONFile Constructor Tests
// ************************************************
TEST_F(TJSONFile, Constructor_EmptyString_IsLoadedReturnsFalse)
{
	JSONFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TJSONFile, Constructor_BadPathSpecified_IsLoadedReturnsFalse)
{
	JSONFile jfile(BAD_PATH);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TJSONFile, Constructor_NoneExistentFile_IsLoadedReturnsFalse)
{
	JSONFile jfile(NONE_EXISTENT_FILE);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TJSONFile, Constructor_SaveNewFile_SaveReturnsTrue)
{
	JSONFile jfile(SAVE_NEW_FILE);
	ASSERT_TRUE(jfile.Save());
}

TEST_F(TJSONFile, Constructor_CreateNewFile_NewFileExists)
{
	JSONFile jfile(CREATE_NEW_FILE); jfile.Save();
	ASSERT_TRUE(std::ifstream(CREATE_NEW_FILE).is_open());
}

// ************************************************
// JSONFile Destructor Tests
// ************************************************
TEST_F(TJSONFile, Destructor_OutOfScopeWihtoutSaving_FileExists)
{
	{
		JSONFile jfile(SCOPED_SAVE);
	}
	ASSERT_TRUE(std::ifstream(SCOPED_SAVE).is_open());
}

// ************************************************
// JSONFile::IsLoaded Tests
// ************************************************
TEST_F(TJSONFile, IsLoaded_CreateNewFile_IsLoadedReturnsFalseUntilSave)
{
	JSONFile jfile(IS_LOADED_TEST1);
	ASSERT_FALSE(jfile.IsLoaded());
	jfile.Save();
	ASSERT_TRUE(jfile.IsLoaded());
}

TEST_F(TJSONFile, IsLoaded_LoadExistingFile_IsLoadedReturnsTrue)
{
	JSONFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.IsLoaded());
}

TEST_F(TJSONFile, IsLoaded_LoadExistingMalformedFile_IsLoadedReturnsFalse)
{
	JSONFile jfile(EXISTING_MALFORMED_FILE);
	ASSERT_FALSE(jfile.IsLoaded());
}

// ************************************************
// JSONFile::Set<T> Tests
// ************************************************
TEST_F(TJSONFile, Set_SetBoolTrue_GetBoolReturnsTrue)
{
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<bool>("myBool", true);
	ASSERT_TRUE(jfile.Get<bool>("myBool"));
}

TEST_F(TJSONFile, Set_SetBoolFalse_GetBoolReturnsFalse)
{
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<bool>("myBool", false);
	ASSERT_FALSE(jfile.Get<bool>("myBool"));
}

TEST_F(TJSONFile, Set_SetIntMinus2_GetIntReturnsMinus2)
{
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<s32>("myUInt", -2);
	ASSERT_EQ(jfile.Get<s32>("myUInt"), -2);
}

TEST_F(TJSONFile, Set_SetUInt41_GetUIntReturns41)
{
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<u32>("myInt", 41);
	ASSERT_EQ(jfile.Get<u32>("myInt"), 41);
}

TEST_F(TJSONFile, Set_SetFloatPI_GetFloatReturnsPI)
{
	static const float fPI = 3.14159f;
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<float>("myFloat", fPI);
	ASSERT_EQ(jfile.Get<float>("myFloat"), fPI);
}

TEST_F(TJSONFile, Set_SetDoubleMax_GetDoubleReturnsMax)
{
	static const double max = std::numeric_limits<double>::max();
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<double>("myDouble", max);
	ASSERT_EQ(jfile.Get<double>("myDouble"), max);
}

TEST_F(TJSONFile, Set_SetStringFoo_GetStringReturnsFoo)
{
	JSONFile jfile(EMPTY_STRING);
	jfile.Set<std::string>("myString", "Foo");
	ASSERT_EQ(jfile.Get<std::string>("myString"), "Foo");
}
#endif