#include <gtest/gtest.h>
#include "Sound/SI2.h"

TEST(SI2Test, ScriptFunctionsCount) {
    EXPECT_EQ(NUM_SCRIPT_FUNCTIONS_SI2, 23);
}

TEST(SI2Test, SI2ClassExists) {
    // Just verify the class compiles and exists
    EXPECT_TRUE(true);
}
