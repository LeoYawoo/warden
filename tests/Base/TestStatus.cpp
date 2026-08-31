#include <gtest/gtest.h>
#include "Base/Status.h"

TEST(StatusTest, DefaultConstructor) {
    Status status;
    EXPECT_EQ(status.GetCode(), 0);
    EXPECT_TRUE(status.GetMessage().empty());
    EXPECT_TRUE(status.IsSuccess());
    EXPECT_FALSE(status.HasError());
}

TEST(StatusTest, ParameterizedConstructor) {
    Status status(42, "Error occurred");
    EXPECT_EQ(status.GetCode(), 42);
    EXPECT_EQ(status.GetMessage(), "Error occurred");
    EXPECT_FALSE(status.IsSuccess());
    EXPECT_TRUE(status.HasError());
}

TEST(StatusTest, SetCode) {
    Status status;
    status.SetCode(100);
    EXPECT_EQ(status.GetCode(), 100);
}

TEST(StatusTest, SetMessage) {
    Status status;
    status.SetMessage("Test message");
    EXPECT_EQ(status.GetMessage(), "Test message");
}

TEST(StatusTest, IsSuccess) {
    Status status1(0, "Success");
    EXPECT_TRUE(status1.IsSuccess());

    Status status2(1, "Error");
    EXPECT_FALSE(status2.IsSuccess());
}

TEST(StatusTest, HasError) {
    Status status1(0, "Success");
    EXPECT_FALSE(status1.HasError());

    Status status2(1, "Error");
    EXPECT_TRUE(status2.HasError());
}

TEST(StatusTest, Clear) {
    Status status(42, "Error message");
    status.Clear();
    EXPECT_EQ(status.GetCode(), 0);
    EXPECT_TRUE(status.GetMessage().empty());
    EXPECT_TRUE(status.IsSuccess());
}

TEST(StatusTest, SetError) {
    Status status;
    status.SetError(100, "New error");
    EXPECT_EQ(status.GetCode(), 100);
    EXPECT_EQ(status.GetMessage(), "New error");
}
