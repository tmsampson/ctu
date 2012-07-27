#include <gtest/gtest.h>
#include "tests/dummyTest.h"

int main(int argc, char* argv[])
{
    // Initialise and run tests
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
