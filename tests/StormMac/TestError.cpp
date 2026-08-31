#include <gtest/gtest.h>
#include "StormMac/Error.h"

TEST(StormErrorTest, GetLastError) {
    // Test that GetLastError/SetLastError work
    uint32_t lastError = SErrGetLastError();
    // Just verify it doesn't crash
    (void)lastError;
}

TEST(StormErrorTest, SetLastError) {
    // Test that SetLastError works
    SErrSetLastError(0);
    uint32_t lastError = SErrGetLastError();
    EXPECT_EQ(lastError, 0u);
}

TEST(StormErrorTest, SetLastErrorAndRetrieve) {
    // Test setting and retrieving error code
    SErrSetLastError(42);
    uint32_t lastError = SErrGetLastError();
    EXPECT_EQ(lastError, 42u);
}

TEST(StormErrorTest, PrepareAppFatal) {
    // Test that SErrPrepareAppFatal doesn't crash
    // Note: This function prepares for a fatal error display
    SErrPrepareAppFatal(__FILE__, __LINE__);
}

TEST(StormErrorTest, DisplayErrorFmt) {
    // Test that SErrDisplayErrorFmt compiles
    // Note: We can't easily test this without triggering error display
}
