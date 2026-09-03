#include <gtest/gtest.h>
#include "System/PersistentPath.h"
#include "System/MacShell/MainApp.h"
#include "System/Storm/H/SAPIExtend.h"
#include "System/Storm/H/stpl.h"
#include "System/Utility/CFStringUtilities.h"

// Test PersistentPath
TEST(PersistentPathTest, DefaultConstructor) {
    PersistentPath path;
    EXPECT_FALSE(path.IsInitialized());
}

TEST(PersistentPathTest, Initialize) {
    PersistentPath path;
    EXPECT_TRUE(path.Initialize());
    EXPECT_TRUE(path.IsInitialized());
}

TEST(PersistentPathTest, SetBasePath) {
    PersistentPath path;
    path.SetBasePath("/usr/local/games");
    EXPECT_STREQ(path.GetBasePath(), "/usr/local/games");
}

TEST(PersistentPathTest, SetUserDataPath) {
    PersistentPath path;
    path.SetUserDataPath("/home/user/.war3");
    EXPECT_STREQ(path.GetUserDataPath(), "/home/user/.war3");
}

TEST(PersistentPathTest, SetSavePath) {
    PersistentPath path;
    path.SetSavePath("/home/user/.war3/save");
    EXPECT_STREQ(path.GetSavePath(), "/home/user/.war3/save");
}

// Test MainApp
TEST(MainAppTest, DefaultConstructor) {
    MainApp app;
    EXPECT_FALSE(app.IsInitialized());
    EXPECT_FALSE(app.IsRunning());
}

TEST(MainAppTest, Initialize) {
    MainApp app;
    EXPECT_TRUE(app.Initialize());
    EXPECT_TRUE(app.IsInitialized());
    EXPECT_TRUE(app.IsRunning());
}

TEST(MainAppTest, SetAppName) {
    MainApp app;
    app.SetAppName("Warcraft III");
    EXPECT_STREQ(app.GetAppName(), "Warcraft III");
}

TEST(MainAppTest, SetVersion) {
    MainApp app;
    app.SetVersion("1.26a");
    EXPECT_STREQ(app.GetVersion(), "1.26a");
}

TEST(MainAppTest, Shutdown) {
    MainApp app;
    app.Initialize();
    app.Shutdown();
    EXPECT_FALSE(app.IsInitialized());
    EXPECT_FALSE(app.IsRunning());
}

// Test Storm templates
TEST(StormTemplateTest, Swap) {
    int a = 5, b = 10;
    Storm::Swap(a, b);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);
}

TEST(StormTemplateTest, Min) {
    EXPECT_EQ(Storm::Min(5, 10), 5);
    EXPECT_EQ(Storm::Min(10, 5), 5);
}

TEST(StormTemplateTest, Max) {
    EXPECT_EQ(Storm::Max(5, 10), 10);
    EXPECT_EQ(Storm::Max(10, 5), 10);
}

TEST(StormTemplateTest, Clamp) {
    EXPECT_EQ(Storm::Clamp(5, 0, 10), 5);
    EXPECT_EQ(Storm::Clamp(-5, 0, 10), 0);
    EXPECT_EQ(Storm::Clamp(15, 0, 10), 10);
}

// Test CFStringUtilities
TEST(CFStringUtilitiesTest, IsEmpty) {
    EXPECT_TRUE(CFString::IsEmpty(nullptr));
    EXPECT_TRUE(CFString::IsEmpty(""));
    EXPECT_FALSE(CFString::IsEmpty("test"));
}

TEST(CFStringUtilitiesTest, GetLength) {
    EXPECT_EQ(CFString::GetLength(nullptr), 0u);
    EXPECT_EQ(CFString::GetLength(""), 0u);
    EXPECT_EQ(CFString::GetLength("test"), 4u);
}

TEST(CFStringUtilitiesTest, Compare) {
    EXPECT_EQ(CFString::Compare("abc", "abc"), 0);
    EXPECT_TRUE(CFString::Compare("abc", "def") < 0);
    EXPECT_TRUE(CFString::Compare("def", "abc") > 0);
}

TEST(CFStringUtilitiesTest, CompareIgnoreCase) {
    EXPECT_EQ(CFString::CompareIgnoreCase("ABC", "abc"), 0);
    EXPECT_TRUE(CFString::CompareIgnoreCase("abc", "DEF") < 0);
}
