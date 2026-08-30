#include <gtest/gtest.h>
#include "Agile/CStatus.h"

TEST(CStatusTest, DefaultConstructor) {
    CStatus status;
    EXPECT_TRUE(status.IsEmpty());
    EXPECT_EQ(status.GetCount(), 0u);
}

TEST(CStatusTest, AddSingleEntry) {
    CStatus status;
    status.Add(STATUS_INFO, "Test message");
    EXPECT_FALSE(status.IsEmpty());
    EXPECT_EQ(status.GetCount(), 1u);
    EXPECT_EQ(status.GetEntry(0).type, STATUS_INFO);
    EXPECT_STREQ(status.GetEntry(0).message, "Test message");
}

TEST(CStatusTest, AddMultipleEntries) {
    CStatus status;
    status.Add(STATUS_INFO, "Info message");
    status.Add(STATUS_WARNING, "Warning message");
    status.Add(STATUS_ERROR, "Error message");
    EXPECT_EQ(status.GetCount(), 3u);
    EXPECT_EQ(status.GetEntry(0).type, STATUS_INFO);
    EXPECT_EQ(status.GetEntry(1).type, STATUS_WARNING);
    EXPECT_EQ(status.GetEntry(2).type, STATUS_ERROR);
}

TEST(CStatusTest, AddFormattedMessage) {
    CStatus status;
    status.Add(STATUS_INFO, "Value: %d, Name: %s", 42, "test");
    EXPECT_EQ(status.GetCount(), 1u);
    EXPECT_STREQ(status.GetEntry(0).message, "Value: 42, Name: test");
}

TEST(CStatusTest, GetHighestSeverity) {
    CStatus status;
    status.Add(STATUS_INFO, "Info");
    status.Add(STATUS_WARNING, "Warning");
    status.Add(STATUS_ERROR, "Error");
    EXPECT_EQ(status.GetHighestSeverity(), STATUS_ERROR);
}

TEST(CStatusTest, GetHighestSeverityFatal) {
    CStatus status;
    status.Add(STATUS_INFO, "Info");
    status.Add(STATUS_FATAL, "Fatal");
    EXPECT_EQ(status.GetHighestSeverity(), STATUS_FATAL);
}

TEST(CStatusTest, Clear) {
    CStatus status;
    status.Add(STATUS_INFO, "Message 1");
    status.Add(STATUS_WARNING, "Message 2");
    EXPECT_EQ(status.GetCount(), 2u);

    status.Clear();
    EXPECT_TRUE(status.IsEmpty());
    EXPECT_EQ(status.GetCount(), 0u);
}

TEST(CStatusTest, AddFromAnotherStatus) {
    CStatus status1;
    status1.Add(STATUS_INFO, "Message 1");

    CStatus status2;
    status2.Add(STATUS_WARNING, "Message 2");

    status1.Add(status2);
    EXPECT_EQ(status1.GetCount(), 2u);
    EXPECT_EQ(status1.GetEntry(0).type, STATUS_INFO);
    EXPECT_EQ(status1.GetEntry(1).type, STATUS_WARNING);
}

TEST(CStatusTest, GlobalStatusObject) {
    CStatus &global = GetGlobalStatusObj();
    // Just verify we can get the global object
    EXPECT_TRUE(&global != nullptr);
}

TEST(CStatusTest, SeverityLevels) {
    EXPECT_EQ(STATUS_INFO, 0);
    EXPECT_EQ(STATUS_WARNING, 1);
    EXPECT_EQ(STATUS_ERROR, 2);
    EXPECT_EQ(STATUS_FATAL, 3);
    EXPECT_EQ(STATUS_NUMTYPES, 4);
}
