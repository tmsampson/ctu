#ifndef DUMMY_TEST_H_
#define DUMMY_TEST_H_

#include <gtest/gtest.h>
#include "dummy.h"

class TDummyTest : public ::testing::Test
{
};

TEST_F(TDummyTest, AdditionTest)
{
	ASSERT_EQ(add<int>(10, 2), 12);
}

#endif
