#ifndef T_JSONFILE_H_
#define T_JSONFILE_H_

#include <gtest/gtest.h>
#include "JSONFile.h"

class TJSONFile : public ::testing::Test
{
};

TEST_F(TJSONFile, Constructor_BlankString_IsLoadedFalse)
{
	JSONFile jfile("");
	ASSERT_EQ(jfile.IsLoaded(), false);
}

#endif
