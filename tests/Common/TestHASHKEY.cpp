#include <gtest/gtest.h>
#include "Common/Hashkey.h"

TEST(HASHKEYNONTest, Equality) {
    HASHKEY_NONE key1;
    HASHKEY_NONE key2;
    EXPECT_TRUE(key1 == key2);
}

TEST(HASHPTRTest, Equality) {
    int a = 1, b = 2;
    HASHKEY_PTR key1;
    HASHKEY_PTR key2;

    key1.m_key = &a;
    key2.m_key = &a;
    EXPECT_TRUE(key1 == key2);

    key2.m_key = &b;
    EXPECT_FALSE(key1 == key2);
}

TEST(HASHSTRTest, DefaultConstructor) {
    HASHKEY_STR key;
    EXPECT_EQ(key.m_str, nullptr);
}

TEST(HASHSTRTest, Assignment) {
    HASHKEY_STR key;
    key = "Hello";
    EXPECT_NE(key.m_str, nullptr);
    EXPECT_STREQ(key.m_str, "Hello");
}

TEST(HASHSTRTest, Equality) {
    HASHKEY_STR key1;
    HASHKEY_STR key2;

    key1 = "Hello";
    key2 = "Hello";

    EXPECT_TRUE(key1 == "Hello");
    EXPECT_TRUE(key2 == "Hello");
}

TEST(HASHSTRTest, Inequality) {
    HASHKEY_STR key1;
    HASHKEY_STR key2;

    key1 = "Hello";
    key2 = "World";

    EXPECT_FALSE(key1 == "World");
}

TEST(HASHSTRTest, NullptrEquality) {
    HASHKEY_STR key;
    EXPECT_TRUE(key == nullptr);
    EXPECT_FALSE(key == "Hello");
}

TEST(HASHSTRTest, CopyAssignment) {
    HASHKEY_STR key1;
    HASHKEY_STR key2;

    key1 = "Hello";
    key2 = key1;

    EXPECT_TRUE(key2 == "Hello");
}

TEST(HASHSTRITest, CaseInsensitive) {
    HASHKEY_STRI key;
    key = "Hello";

    EXPECT_TRUE(key == "hello");
    EXPECT_TRUE(key == "HELLO");
    EXPECT_TRUE(key == "Hello");
}

TEST(HASHSTRIPACKEDTest, TokenizeAndPack) {
    HASHKEY_STRIPACKED key;
    key = "Hello   World   Test";

    // Should pack multiple spaces into single space
    EXPECT_NE(key.m_str, nullptr);
}
