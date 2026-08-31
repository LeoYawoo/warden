#include <gtest/gtest.h>
#include "Base/RCString.h"

TEST(RCStringTest, DefaultConstructor) {
    RCString str;
    EXPECT_TRUE(str.IsEmpty());
    EXPECT_EQ(str.Length(), 0u);
    EXPECT_STREQ(str.c_str(), "");
}

TEST(RCStringTest, CStringConstructor) {
    RCString str("Hello, World!");
    EXPECT_FALSE(str.IsEmpty());
    EXPECT_EQ(str.Length(), 13u);
    EXPECT_STREQ(str.c_str(), "Hello, World!");
}

TEST(RCStringTest, NullStringConstructor) {
    RCString str(nullptr);
    EXPECT_TRUE(str.IsEmpty());
    EXPECT_EQ(str.Length(), 0u);
    EXPECT_STREQ(str.c_str(), "");
}

TEST(RCStringTest, CopyConstructor) {
    RCString str1("Hello");
    RCString str2(str1);
    EXPECT_STREQ(str2.c_str(), "Hello");
    EXPECT_EQ(str2.Length(), 5u);
}

TEST(RCStringTest, MoveConstructor) {
    RCString str1("Hello");
    RCString str2(std::move(str1));
    EXPECT_STREQ(str2.c_str(), "Hello");
    EXPECT_TRUE(str1.IsEmpty());
}

TEST(RCStringTest, CopyAssignment) {
    RCString str1("Hello");
    RCString str2;
    str2 = str1;
    EXPECT_STREQ(str2.c_str(), "Hello");
}

TEST(RCStringTest, MoveAssignment) {
    RCString str1("Hello");
    RCString str2;
    str2 = std::move(str1);
    EXPECT_STREQ(str2.c_str(), "Hello");
    EXPECT_TRUE(str1.IsEmpty());
}

TEST(RCStringTest, CStringAssignment) {
    RCString str;
    str = "Test";
    EXPECT_STREQ(str.c_str(), "Test");
}

TEST(RCStringTest, Equality) {
    RCString str1("Hello");
    RCString str2("Hello");
    RCString str3("World");

    EXPECT_TRUE(str1 == str2);
    EXPECT_FALSE(str1 == str3);
}

TEST(RCStringTest, CStringEquality) {
    RCString str("Hello");
    EXPECT_TRUE(str == "Hello");
    EXPECT_FALSE(str == "World");
    EXPECT_TRUE(str == str);  // Self comparison
}

TEST(RCStringTest, Inequality) {
    RCString str1("Hello");
    RCString str2("World");

    EXPECT_TRUE(str1 != str2);
}

TEST(RCStringTest, Clear) {
    RCString str("Hello");
    EXPECT_FALSE(str.IsEmpty());

    str.Clear();
    EXPECT_TRUE(str.IsEmpty());
    EXPECT_STREQ(str.c_str(), "");
}

TEST(RCStringTest, ToString) {
    RCString str("Hello");
    std::string stdStr = str.ToString();
    EXPECT_EQ(stdStr, "Hello");
}

TEST(RCStringTest, Length) {
    RCString str("Hello");
    EXPECT_EQ(str.Length(), 5u);

    RCString empty;
    EXPECT_EQ(empty.Length(), 0u);
}
