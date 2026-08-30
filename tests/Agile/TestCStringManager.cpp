#include <gtest/gtest.h>
#include "Agile/CStringManager.h"

TEST(CStringManagerTest, Singleton) {
    CStringManager *mgr1 = CStringManager::Get();
    CStringManager *mgr2 = CStringManager::Get();
    EXPECT_EQ(mgr1, mgr2);
    EXPECT_NE(mgr1, nullptr);
}

TEST(CStringManagerTest, AddString) {
    CStringManager *mgr = CStringManager::Get();
    const char *str1 = mgr->Add("Hello");
    const char *str2 = mgr->Add("World");
    EXPECT_NE(str1, nullptr);
    EXPECT_NE(str2, nullptr);
    EXPECT_STREQ(str1, "Hello");
    EXPECT_STREQ(str2, "World");
}

TEST(CStringManagerTest, AddDuplicateString) {
    CStringManager *mgr = CStringManager::Get();
    const char *str1 = mgr->Add("Test");
    const char *str2 = mgr->Add("Test");
    EXPECT_EQ(str1, str2);  // Should return same pointer for same string
}

TEST(CStringManagerTest, AddEmptyString) {
    CStringManager *mgr = CStringManager::Get();
    const char *str = mgr->Add("");
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, "");
}

TEST(CStringManagerTest, AddMultipleStrings) {
    CStringManager *mgr = CStringManager::Get();
    const char *str1 = mgr->Add("First");
    const char *str2 = mgr->Add("Second");
    const char *str3 = mgr->Add("Third");
    EXPECT_STREQ(str1, "First");
    EXPECT_STREQ(str2, "Second");
    EXPECT_STREQ(str3, "Third");
    EXPECT_NE(str1, str2);
    EXPECT_NE(str2, str3);
}

TEST(CStringManagerTest, AddLongString) {
    CStringManager *mgr = CStringManager::Get();
    char longStr[1024];
    memset(longStr, 'A', sizeof(longStr) - 1);
    longStr[sizeof(longStr) - 1] = '\0';

    const char *str = mgr->Add(longStr);
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, longStr);
}

TEST(CStringManagerTest, AddStringWithSpecialChars) {
    CStringManager *mgr = CStringManager::Get();
    const char *str = mgr->Add("Hello\tWorld\n!");
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, "Hello\tWorld\n!");
}
