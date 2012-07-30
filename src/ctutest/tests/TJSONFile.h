#ifndef T_JSONFILE_H_
#define T_JSONFILE_H_

#include <gtest/gtest.h>
#include "JSONFile.h"
#include <stdio.h>

class TJSONFile : public ::testing::Test
{
};

TEST_F(TJSONFile, Constructor_BlankString_IsLoadedFalse)
{
	JSONFile jfile("");
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TJSONFile, Constructor_NoneExistentFile_IsLoadedFalse)
{
	JSONFile jfile("unit_test_resources/none-existent-file");
	ASSERT_FALSE(jfile.IsLoaded());
}

TEST_F(TJSONFile, Constructor_CreateNewFile_IsLoadedFalse)
{
	JSONFile jfile("unit_test_resources/new-file");
	ASSERT_TRUE(jfile.Save());
}
#endif