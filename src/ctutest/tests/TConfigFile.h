#ifndef T_CONFIGFILE_H_
#define T_CONFIGFILE_H_

#include "ConfigFile.h"
#include "Common.h"
#include "BasicTypes.h"
#include <gtest/gtest.h>
#include <limits>

class TConfigFile : public ::testing::Test { };
static const char*  SAVE_NEW_FILE                    = "ctutest_resources/save-new-file";
static const char*  CREATE_NEW_FILE                  = "ctutest_resources/create-new-file";
static const char*  CREATE_EMPTY_FILE                = "ctutest_resources/create-empty-file";
static const char*  SCOPED_SAVE                      = "ctutest_resources/scoped-save";
static const char*  IS_LOADED_TEST1                  = "ctutest_resources/is-loaded";
static const char*  MODIFIED_FILE                    = "ctutest_resources/modified-file";
static const char*  EXISTING_MALFORMED_FILE          = "ctutest_resources/existing-malformed-file";
static const u32    EXISTING_MALFORMED_FILE_SIZE     = 29;
static const char*  EXISTING_MALFORMED_FILE_CONTENTS = "I am clearly not a JSON file!";
static const float  PI                               = 3.14159f;
static const double PI_ACCURATE                      = 3.1415926535897932384626433832795028841;
static const double MAX_DOUBLE                       = std::numeric_limits<double>::max();

bool MalformedFileIsUnchanged()
{
	// Note: Read contents and file size to ensure
	//       no change to file on disk.
	std::ifstream fstream(EXISTING_MALFORMED_FILE);
	std::string contents(""); std::getline(fstream, contents);
	std::streamoff fileSize = Utils::GetFileSize(EXISTING_MALFORMED_FILE);

	return (fileSize == EXISTING_MALFORMED_FILE_SIZE &&
	        contents == EXISTING_MALFORMED_FILE_CONTENTS);
}

// ************************************************
// ConfigFile Constructor Tests
// ************************************************
TEST_F(TConfigFile, Constructor_EmptyString_IsLoadedReturnsFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TConfigFile, Constructor_BadPathSpecified_IsLoadedReturnsFalse)
{
	ConfigFile jfile(BAD_PATH);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TConfigFile, Constructor_NoneExistentFile_IsLoadedReturnsFalse)
{
	ConfigFile jfile(NONE_EXISTENT_FILE);
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TConfigFile, Constructor_SaveNewFile_SaveReturnsTrue)
{
	ConfigFile jfile(SAVE_NEW_FILE);
	ASSERT_TRUE(jfile.Save());
}

TEST_F(TConfigFile, Constructor_CreateNewFile_NewFileExists)
{
	ConfigFile jfile(CREATE_NEW_FILE); jfile.Save();
	ASSERT_TRUE(Utils::FileExists(CREATE_NEW_FILE));
}

// ************************************************
// ConfigFile Destructor Tests
// ************************************************
TEST_F(TConfigFile, Destructor_OutOfScopeWihtoutSaving_FileExists)
{
	{
		ConfigFile jfile(SCOPED_SAVE);
	}
	ASSERT_TRUE(Utils::FileExists(SCOPED_SAVE));
}

TEST_F(TConfigFile, Destructor_OutOfScopeMalformedFile_FileUnchanged)
{
	{
		ConfigFile jfile(EXISTING_MALFORMED_FILE);
	}

	ASSERT_TRUE(MalformedFileIsUnchanged());
}

// ************************************************
// ConfigFile Save Tests
// ************************************************
TEST_F(TConfigFile, Save_MalformedFile_FileUnchanged)
{
	ConfigFile jfile(EXISTING_MALFORMED_FILE);
	jfile.Save();
	ASSERT_TRUE(MalformedFileIsUnchanged());
}

// ************************************************
// ConfigFile::IsLoaded Tests
// ************************************************
TEST_F(TConfigFile, IsLoaded_CreateNewFile_ReturnFalseUntilSave)
{
	ConfigFile jfile(IS_LOADED_TEST1);
	ASSERT_FALSE(jfile.IsLoaded());
	jfile.Save();
	ASSERT_TRUE(jfile.IsLoaded());
}

TEST_F(TConfigFile, IsLoaded_LoadExistingFile_ReturnTrue)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.IsLoaded());
}

TEST_F(TConfigFile, IsLoaded_LoadExistingMalformedFile_ReturnFalse)
{
	ConfigFile jfile(EXISTING_MALFORMED_FILE);
	ASSERT_FALSE(jfile.IsLoaded());
}

// ************************************************
// ConfigFile::Set<T> Tests
// ************************************************
TEST_F(TConfigFile, Set_SetBoolTrue_GetBoolReturnsTrue)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<bool>("myBool", true);
	ASSERT_TRUE(jfile.Get<bool>("myBool"));
}

TEST_F(TConfigFile, Set_SetBoolFalse_GetBoolReturnsFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<bool>("myBool", false);
	ASSERT_FALSE(jfile.Get<bool>("myBool"));
}

TEST_F(TConfigFile, Set_SetIntMinus2_GetIntReturnsMinus2)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<s32>("myUInt", -2);
	ASSERT_EQ(-2, jfile.Get<s32>("myUInt"));
}

TEST_F(TConfigFile, Set_SetUInt41_GetUIntReturns41)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<u32>("myInt", 41);
	ASSERT_EQ(41, jfile.Get<u32>("myInt"));
}

TEST_F(TConfigFile, Set_SetFloatPI_GetFloatReturnsPI)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<float>("myFloat", PI);
	ASSERT_EQ(PI, jfile.Get<float>("myFloat"));
}

TEST_F(TConfigFile, Set_SetDoubleMax_GetDoubleReturnsMax)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<double>("myDouble", MAX_DOUBLE);
	ASSERT_EQ(MAX_DOUBLE, jfile.Get<double>("myDouble"));
}

TEST_F(TConfigFile, Set_SetStringFoo_GetStringReturnsFoo)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<std::string>("myString", "Foo");
	ASSERT_EQ("Foo", jfile.Get<std::string>("myString"));
}

TEST_F(TConfigFile, Set_SuplyBlankKey_ReturnFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.Set<u32>("", 101));
}

TEST_F(TConfigFile, Set_OverWriteExistingValue_GetReturnsNewValue)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<std::string>("myString", "Foo");
	ASSERT_EQ("Foo", jfile.Get<std::string>("myString"));
	jfile.Set<std::string>("myString", "Bar");
	ASSERT_EQ("Bar", jfile.Get<std::string>("myString"));
}

TEST_F(TConfigFile, Set_ModifyValueSaveImmediate_NewValueSavedToFile)
{
	ConfigFile jfile(MODIFIED_FILE);
	ASSERT_TRUE(jfile.Get<bool>("myBool"));
	jfile.Set<bool>("myBool", false, true);
	ASSERT_FALSE(ConfigFile(MODIFIED_FILE).Get<bool>("myBool"));
}

TEST_F(TConfigFile, Set_NewKeySaveImmediate_NewKeySavedToFile)
{
	ConfigFile jfile(MODIFIED_FILE);
	ASSERT_FALSE(jfile.ContainsKey("newkey"));
	jfile.Set<int>("newKey", 100, true);
	ASSERT_EQ(100, ConfigFile(MODIFIED_FILE).Get<int>("newKey"));
}

TEST_F(TConfigFile, Set_RemoveKeySaveImmediate_KeyRemovedFromFile)
{
	ConfigFile jfile(MODIFIED_FILE);
	ASSERT_TRUE(jfile.ContainsKey("myBool"));
	jfile.Remove("myBool", true);
	ASSERT_FALSE(ConfigFile(MODIFIED_FILE).ContainsKey("myBool"));
}

// ************************************************
// ConfigFile::ContainsKey<T> Tests
// ************************************************
TEST_F(TConfigFile, ContainsKey_TestInvalidKey_ReturnFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.ContainsKey("Foo"));
}

TEST_F(TConfigFile, ContainsKey_TestExistingKey_ReturnTrue)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<u32>("WeeksInYear", 52);
	ASSERT_TRUE(jfile.ContainsKey("WeeksInYear"));
}

TEST_F(TConfigFile, ContainsKey_TestEmptyKey_ReturnFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.ContainsKey(""));
}

// ************************************************
// ConfigFile::Get<T> Tests
// ************************************************
TEST_F(TConfigFile, Get_GetFromExistingFile_AllValuesCorrect)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(true, jfile.Get<bool>("myBool"));
	ASSERT_EQ(-2, jfile.Get<s32>("myInt"));
	ASSERT_EQ(41, jfile.Get<u32>("myUInt"));
	ASSERT_EQ(PI, jfile.Get<float>("myFloat"));
	ASSERT_EQ(PI_ACCURATE, jfile.Get<double>("myDouble"));
	ASSERT_EQ("Foo", jfile.Get<std::string>("myString"));
}

TEST_F(TConfigFile, Get_SupplyDefaultUIntVal_ReturnDefaultUIntVal)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_EQ(52, jfile.Get<u32>("WeeksInYear", 52));
}

TEST_F(TConfigFile, Get_SupplyDefaultStringVal_ReturnDefaultStringVal)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_EQ("Norris", jfile.Get<std::string>("Chuck", "Norris"));
}

TEST_F(TConfigFile, Get_SupplyDefaultInt_DefaultValueIgnored)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(-2, jfile.Get<s32>("myInt", 100));
}

TEST_F(TConfigFile, Get_SupplyDefaultString_DefaultValueIgnored)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("Foo", jfile.Get<std::string>("myString", "Bar"));
}

// ************************************************
// ConfigFile::Get<T> Type Cast Tests
// ************************************************
TEST_F(TConfigFile, Get_IntAsBool_ReturnTrue)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.Get<bool>("myInt"));
}

TEST_F(TConfigFile, Get_UIntAsBool_ReturnTrue)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.Get<bool>("myUInt"));
}

TEST_F(TConfigFile, Get_BoolAsInt_Return1)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(1, jfile.Get<s32>("myBool"));
}

TEST_F(TConfigFile, Get_UIntAsInt_Return41)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(41, jfile.Get<s32>("myUInt"));
}

TEST_F(TConfigFile, Get_FloatAsInt_Return3)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(3, jfile.Get<s32>("myFloat"));
}

TEST_F(TConfigFile, Get_StringAsInt_Return2468)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(2468, jfile.Get<s32>("myStringInt"));
}

TEST_F(TConfigFile, Get_BoolAsUInt_ReturnOne)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(1, jfile.Get<u32>("myBool"));
}

TEST_F(TConfigFile, Get_FloatAsUInt_Return3)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(3, jfile.Get<u32>("myFloat"));
}

TEST_F(TConfigFile, Get_StringAsUInt_Return2468)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ(2468, jfile.Get<u32>("myStringInt"));
}

TEST_F(TConfigFile, Get_IntAsString_ReturnValidString)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("-2", jfile.Get<std::string>("myInt"));
}

TEST_F(TConfigFile, Get_UIntAsString_ReturnValidString)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("41", jfile.Get<std::string>("myUInt"));
}

TEST_F(TConfigFile, Get_BoolAsString_ReturnValidString)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("true", jfile.Get<std::string>("myBool"));
}

TEST_F(TConfigFile, Get_FloatAsString_ReturnValidString)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("3.141590", jfile.Get<std::string>("myFloat"));
}

TEST_F(TConfigFile, Get_DoubleAsString_ReturnValidTruncatedString)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_EQ("3.141592653589793", jfile.Get<std::string>("myDouble"));
}

// ************************************************
// ConfigFile::Remove Tests
// ************************************************
TEST_F(TConfigFile, Remove_EmptyKey_ReturnFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.Remove(""));
}

TEST_F(TConfigFile, Remove_NoneExistentKey_ReturnFalse)
{
	ConfigFile jfile(EMPTY_STRING);
	ASSERT_FALSE(jfile.Remove("non-existent-key"));
}

TEST_F(TConfigFile, Remove_ExistingKey_ReturnTrue)
{
	ConfigFile jfile(EMPTY_STRING);
	jfile.Set<s32>("existing-key", 0);
	ASSERT_TRUE(jfile.Remove("existing-key"));
	ASSERT_FALSE(jfile.ContainsKey("existing-key"));
}

TEST_F(TConfigFile, Remove_RemoveAndSave_ValueRemovedFromFile)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.ContainsKey("myString"));
	ASSERT_TRUE(jfile.Remove("myString"));
	jfile.Save();
	ASSERT_FALSE(ConfigFile(EXISTING_FILE).ContainsKey("myString"));
}

TEST_F(TConfigFile, Remove_RemoveAndOutOfScope_ValueRemovedFromFile)
{
	{
		ConfigFile jfile(EXISTING_FILE);
		ASSERT_TRUE(jfile.ContainsKey("myDouble"));
		ASSERT_TRUE(jfile.Remove("myDouble"));
	}
	ASSERT_FALSE(ConfigFile(EXISTING_FILE).ContainsKey("myDouble"));
}

// ************************************************
// ConfigFile::Clear Tests
// ************************************************
TEST_F(TConfigFile, Clear_ClearEmptyConfigFile_ReturnTrue)
{
	ConfigFile jfile(CREATE_EMPTY_FILE);
	ASSERT_TRUE(jfile.Clear());
}

TEST_F(TConfigFile, Clear_ClearNonEmptyConfigFile_KeyRemovedAfterClear)
{
	ConfigFile jfile(CREATE_EMPTY_FILE);
	jfile.Set<bool>("keyToClear", true);
	ASSERT_TRUE(jfile.ContainsKey("keyToClear"));
	ASSERT_TRUE(jfile.Clear());
	ASSERT_FALSE(jfile.ContainsKey("keyToClear"));
}

TEST_F(TConfigFile, Clear_ClearExistingConfigFile_AllKeysRemovedAfterClear)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_TRUE(jfile.Clear());
	ASSERT_FALSE(jfile.ContainsKey("myBool"));
	ASSERT_FALSE(jfile.ContainsKey("myInt"));
	ASSERT_FALSE(jfile.ContainsKey("myUInt"));
	ASSERT_FALSE(jfile.ContainsKey("myFloat"));
	ASSERT_FALSE(jfile.ContainsKey("myDouble"));
	ASSERT_FALSE(jfile.ContainsKey("myString"));
	ASSERT_FALSE(jfile.ContainsKey("myStringInt"));
}

TEST_F(TConfigFile, Clear_LoadPreviouslyClearedConfigFile_ConfigFileEmpty)
{
	ConfigFile jfile(EXISTING_FILE);
	ASSERT_FALSE(jfile.ContainsKey("myBool"));
	ASSERT_FALSE(jfile.ContainsKey("myInt"));
	ASSERT_FALSE(jfile.ContainsKey("myUInt"));
	ASSERT_FALSE(jfile.ContainsKey("myFloat"));
	ASSERT_FALSE(jfile.ContainsKey("myDouble"));
	ASSERT_FALSE(jfile.ContainsKey("myString"));
	ASSERT_FALSE(jfile.ContainsKey("myStringInt"));
}
#endif