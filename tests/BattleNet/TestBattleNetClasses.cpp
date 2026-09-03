#include <gtest/gtest.h>
#include "BattleNet/BattleNetCache.h"
#include "BattleNet/BattleNetChat.h"
#include <cstring>

// Test BattleNetCache
TEST(BattleNetCacheTest, DefaultConstructor) {
    BattleNetCache cache;
    EXPECT_EQ(cache.GetCount(), 0u);
    EXPECT_EQ(cache.GetTotalSize(), 0u);
    EXPECT_EQ(cache.GetMaxSize(), 0xFFFFFFFFu);
}

TEST(BattleNetCacheTest, Add) {
    BattleNetCache cache;
    int data = 42;
    EXPECT_TRUE(cache.Add("key1", &data, sizeof(data)));
    EXPECT_TRUE(cache.Has("key1"));
    EXPECT_EQ(cache.GetCount(), 1u);
}

TEST(BattleNetCacheTest, Get) {
    BattleNetCache cache;
    int data = 42;
    cache.Add("key1", &data, sizeof(data));

    int result = 0;
    EXPECT_TRUE(cache.Get("key1", &result, sizeof(result)));
    EXPECT_EQ(result, 42);
}

TEST(BattleNetCacheTest, Remove) {
    BattleNetCache cache;
    int data = 42;
    cache.Add("key1", &data, sizeof(data));
    EXPECT_TRUE(cache.Remove("key1"));
    EXPECT_FALSE(cache.Has("key1"));
    EXPECT_EQ(cache.GetCount(), 0u);
}

TEST(BattleNetCacheTest, Clear) {
    BattleNetCache cache;
    int data = 42;
    cache.Add("key1", &data, sizeof(data));
    cache.Add("key2", &data, sizeof(data));
    cache.Clear();
    EXPECT_EQ(cache.GetCount(), 0u);
    EXPECT_EQ(cache.GetTotalSize(), 0u);
}

TEST(BattleNetCacheTest, SetMaxSize) {
    BattleNetCache cache;
    cache.SetMaxSize(100);
    EXPECT_EQ(cache.GetMaxSize(), 100u);
}

// Test BattleNetChat
TEST(BattleNetChatTest, DefaultConstructor) {
    BattleNetChat chat;
    EXPECT_FALSE(chat.IsInChannel());
    EXPECT_EQ(chat.GetMessageCount(), 0u);
    EXPECT_EQ(chat.GetMaxMessages(), 100u);
}

TEST(BattleNetChatTest, JoinChannel) {
    BattleNetChat chat;
    EXPECT_TRUE(chat.JoinChannel("General"));
    EXPECT_TRUE(chat.IsInChannel());
    EXPECT_STREQ(chat.GetCurrentChannel(), "General");
}

TEST(BattleNetChatTest, LeaveChannel) {
    BattleNetChat chat;
    chat.JoinChannel("General");
    chat.LeaveChannel("General");
    EXPECT_FALSE(chat.IsInChannel());
}

TEST(BattleNetChatTest, AddMessage) {
    BattleNetChat chat;
    chat.AddMessage("User1", "Hello World");
    EXPECT_EQ(chat.GetMessageCount(), 1u);
    EXPECT_STREQ(chat.GetMessageSender(0), "User1");
    EXPECT_STREQ(chat.GetMessageContent(0), "Hello World");
}

TEST(BattleNetChatTest, ClearMessages) {
    BattleNetChat chat;
    chat.AddMessage("User1", "Message 1");
    chat.AddMessage("User2", "Message 2");
    chat.ClearMessages();
    EXPECT_EQ(chat.GetMessageCount(), 0u);
}

TEST(BattleNetChatTest, SetMaxMessages) {
    BattleNetChat chat;
    chat.SetMaxMessages(5);
    EXPECT_EQ(chat.GetMaxMessages(), 5u);

    // Add more messages than max
    for (int i = 0; i < 10; i++) {
        char sender[16];
        snprintf(sender, sizeof(sender), "User%d", i);
        chat.AddMessage(sender, "Message");
    }
    EXPECT_EQ(chat.GetMessageCount(), 5u);
}
