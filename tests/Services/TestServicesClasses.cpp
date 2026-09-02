#include <gtest/gtest.h>
#include "Services/AsyncFile.h"
#include "Services/Database.h"
#include "Services/GfxSingletonManager.h"
#include "Services/Lightning.h"
#include "Services/Profile.h"
#include "Services/ProfileInternal.h"
#include "Services/SprAnimList.h"
#include "Services/SprLinkTable.h"
#include "Services/Sprite.h"
#include "Services/SysMessage.h"
#include "Services/TextBlock.h"
#include "Services/Texture.h"
#include "Services/Tokenizer.h"

// Test Database
TEST(DatabaseTest, DefaultConstructor) {
    Database db;
    EXPECT_FALSE(db.IsOpen());
    EXPECT_EQ(db.Count(), 0u);
}

TEST(DatabaseTest, SetGet) {
    Database db;
    db.Set("key1", "value1");
    std::string value;
    EXPECT_TRUE(db.Get("key1", value));
    EXPECT_STREQ(value.c_str(), "value1");
}

TEST(DatabaseTest, Has) {
    Database db;
    db.Set("key1", "value1");
    EXPECT_TRUE(db.Has("key1"));
    EXPECT_FALSE(db.Has("key2"));
}

TEST(DatabaseTest, Delete) {
    Database db;
    db.Set("key1", "value1");
    EXPECT_TRUE(db.Delete("key1"));
    EXPECT_FALSE(db.Has("key1"));
}

TEST(DatabaseTest, Clear) {
    Database db;
    db.Set("key1", "value1");
    db.Set("key2", "value2");
    db.Clear();
    EXPECT_EQ(db.Count(), 0u);
}

// Test GfxSingletonManager
TEST(GfxSingletonManagerTest, GetInstance) {
    GfxSingletonManager& mgr = GfxSingletonManager::GetInstance();
    EXPECT_EQ(mgr.GetCount(), 0u);
}

TEST(GfxSingletonManagerTest, SetGetSingleton) {
    GfxSingletonManager& mgr = GfxSingletonManager::GetInstance();
    int value = 42;
    mgr.SetSingleton("test", &value);
    EXPECT_EQ(mgr.GetSingleton("test"), &value);
}

TEST(GfxSingletonManagerTest, RemoveSingleton) {
    GfxSingletonManager& mgr = GfxSingletonManager::GetInstance();
    int value = 42;
    mgr.SetSingleton("test", &value);
    mgr.RemoveSingleton("test");
    EXPECT_EQ(mgr.GetSingleton("test"), nullptr);
}

// Test Lightning
TEST(LightningTest, DefaultConstructor) {
    Lightning l;
    EXPECT_FALSE(l.IsActive());
    EXPECT_FLOAT_EQ(l.GetWidth(), 1.0f);
}

TEST(LightningTest, SetColor) {
    Lightning l;
    l.SetColor(1.0f, 0.5f, 0.0f);
    EXPECT_FLOAT_EQ(l.GetRed(), 1.0f);
    EXPECT_FLOAT_EQ(l.GetGreen(), 0.5f);
    EXPECT_FLOAT_EQ(l.GetBlue(), 0.0f);
}

TEST(LightningTest, SetStartEndPoint) {
    Lightning l;
    l.SetStartPoint(0, 0, 0);
    l.SetEndPoint(100, 100, 100);
    EXPECT_FLOAT_EQ(l.GetStartX(), 0.0f);
    EXPECT_FLOAT_EQ(l.GetEndX(), 100.0f);
}

// Test Profile
TEST(ProfileTest, DefaultConstructor) {
    Profile p;
    EXPECT_FALSE(p.IsLoaded());
    EXPECT_EQ(p.Count(), 0u);
}

TEST(ProfileTest, SetGet) {
    Profile p;
    p.Set("key1", "value1");
    std::string value;
    EXPECT_TRUE(p.Get("key1", value));
    EXPECT_STREQ(value.c_str(), "value1");
}

// Test ProfileInternal
TEST(ProfileInternalTest, DefaultConstructor) {
    ProfileInternal pi;
    EXPECT_TRUE(pi.IsValid());
}

TEST(ProfileInternalTest, SetGetInternal) {
    ProfileInternal pi;
    int data = 42;
    EXPECT_TRUE(pi.SetInternal("key", &data, sizeof(data)));
    int result = 0;
    EXPECT_TRUE(pi.GetInternal("key", &result, sizeof(result)));
    EXPECT_EQ(result, 42);
}

// Test SprAnimList
TEST(SprAnimListTest, DefaultConstructor) {
    SprAnimList list;
    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.GetAnimCount(), 0u);
}

// Test SprLinkTable
TEST(SprLinkTableTest, DefaultConstructor) {
    SprLinkTable table;
    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.GetLinkCount(), 0u);
}

TEST(SprLinkTableTest, AddLink) {
    SprLinkTable table;
    table.AddLink(1, 2);
    EXPECT_TRUE(table.HasLink(1, 2));
    EXPECT_EQ(table.GetLinkCount(), 1u);
}

TEST(SprLinkTableTest, RemoveLink) {
    SprLinkTable table;
    table.AddLink(1, 2);
    table.RemoveLink(1, 2);
    EXPECT_FALSE(table.HasLink(1, 2));
}

TEST(SprLinkTableTest, GetLinks) {
    SprLinkTable table;
    table.AddLink(1, 2);
    table.AddLink(1, 3);
    auto links = table.GetLinks(1);
    EXPECT_EQ(links.size(), 2u);
}

// Test Sprite
TEST(SpriteTest, DefaultConstructor) {
    Sprite s;
    EXPECT_TRUE(s.IsVisible());
    EXPECT_FALSE(s.IsPlaying());
    EXPECT_FLOAT_EQ(s.GetScaleX(), 1.0f);
}

TEST(SpriteTest, SetPosition) {
    Sprite s;
    s.SetPosition(10, 20);
    EXPECT_FLOAT_EQ(s.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(s.GetY(), 20.0f);
}

TEST(SpriteTest, SetScale) {
    Sprite s;
    s.SetScale(2.0f, 3.0f);
    EXPECT_FLOAT_EQ(s.GetScaleX(), 2.0f);
    EXPECT_FLOAT_EQ(s.GetScaleY(), 3.0f);
}

// Test SysMessage
TEST(SysMessageTest, DefaultConstructor) {
    SysMessage msg;
    EXPECT_EQ(msg.GetMessageCount(), 0u);
    EXPECT_EQ(msg.GetDisplayCount(), 10u);
}

TEST(SysMessageTest, AddMessage) {
    SysMessage msg;
    msg.AddMessage("Test message");
    EXPECT_EQ(msg.GetMessageCount(), 1u);
    EXPECT_STREQ(msg.GetMessage(0), "Test message");
}

TEST(SysMessageTest, ClearMessages) {
    SysMessage msg;
    msg.AddMessage("Test");
    msg.ClearMessages();
    EXPECT_EQ(msg.GetMessageCount(), 0u);
}

// Test TextBlock
TEST(TextBlockTest, DefaultConstructor) {
    TextBlock tb;
    EXPECT_FLOAT_EQ(tb.GetWidth(), 0.0f);
    EXPECT_FLOAT_EQ(tb.GetHeight(), 0.0f);
}

TEST(TextBlockTest, SetText) {
    TextBlock tb;
    tb.SetText("Hello World");
    EXPECT_STREQ(tb.GetText(), "Hello World");
}

// Test Texture
TEST(TextureTest, DefaultConstructor) {
    Texture t;
    EXPECT_FALSE(t.IsLoaded());
    EXPECT_EQ(t.GetWidth(), 0u);
}

TEST(TextureTest, Load) {
    Texture t;
    EXPECT_TRUE(t.Load("test.dds"));
    EXPECT_TRUE(t.IsLoaded());
}

// Test Tokenizer
TEST(TokenizerTest, DefaultConstructor) {
    Tokenizer tz;
    EXPECT_FALSE(tz.HasMoreTokens());
}

TEST(TokenizerTest, SetString) {
    Tokenizer tz;
    tz.SetString("Hello World Test");
    EXPECT_TRUE(tz.HasMoreTokens());
}

TEST(TokenizerTest, NextToken) {
    Tokenizer tz;
    tz.SetString("Hello World Test");
    char buffer[256];
    EXPECT_TRUE(tz.NextToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "Hello");
    EXPECT_TRUE(tz.NextToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "World");
    EXPECT_TRUE(tz.NextToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "Test");
}

TEST(TokenizerTest, PeekToken) {
    Tokenizer tz;
    tz.SetString("Hello World");
    char buffer[256];
    EXPECT_TRUE(tz.PeekToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "Hello");
    EXPECT_TRUE(tz.PeekToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "Hello");
}

TEST(TokenizerTest, Reset) {
    Tokenizer tz;
    tz.SetString("Hello World");
    char buffer[256];
    tz.NextToken(buffer, sizeof(buffer));
    tz.Reset();
    EXPECT_TRUE(tz.NextToken(buffer, sizeof(buffer)));
    EXPECT_STREQ(buffer, "Hello");
}

// Test AsyncFile
TEST(AsyncFileTest, DefaultConstructor) {
    AsyncFile af;
    EXPECT_FALSE(af.IsOpen());
    EXPECT_FALSE(af.IsPending());
}
