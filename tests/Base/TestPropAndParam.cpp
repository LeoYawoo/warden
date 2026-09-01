#include <gtest/gtest.h>
#include "Base/Prop.h"
#include "Base/Param.h"

// Test CPropArrayList
TEST(CPropArrayListTest, DefaultConstructor) {
    CPropArrayList<PROPARRAY> list;
    EXPECT_EQ(list.GetCount(), 0u);
}

TEST(CPropArrayListTest, Add) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop;
    prop.id = 1;
    prop.value = 100;
    prop.flags = 0;

    list.Add(prop);
    EXPECT_EQ(list.GetCount(), 1u);
}

TEST(CPropArrayListTest, AddMultiple) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop1;
    prop1.id = 1;
    prop1.value = 100;
    prop1.flags = 0;

    PROPARRAY prop2;
    prop2.id = 2;
    prop2.value = 200;
    prop2.flags = 0;

    list.Add(prop1);
    list.Add(prop2);
    EXPECT_EQ(list.GetCount(), 2u);
}

TEST(CPropArrayListTest, Find) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop;
    prop.id = 1;
    prop.value = 100;
    prop.flags = 0;

    list.Add(prop);
    PROPARRAY* found = list.Find(1);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1u);
    EXPECT_EQ(found->value, 100u);
}

TEST(CPropArrayListTest, FindNotFound) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY* found = list.Find(999);
    EXPECT_EQ(found, nullptr);
}

TEST(CPropArrayListTest, Remove) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop;
    prop.id = 1;
    prop.value = 100;
    prop.flags = 0;

    list.Add(prop);
    EXPECT_EQ(list.GetCount(), 1u);

    list.Remove(1);
    EXPECT_EQ(list.GetCount(), 0u);
}

TEST(CPropArrayListTest, GetByIndex) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop;
    prop.id = 1;
    prop.value = 100;
    prop.flags = 0;

    list.Add(prop);
    PROPARRAY* found = list.GetByIndex(0);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1u);
}

TEST(CPropArrayListTest, GetByIndexOutOfBounds) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY* found = list.GetByIndex(0);
    EXPECT_EQ(found, nullptr);
}

TEST(CPropArrayListTest, Clear) {
    CPropArrayList<PROPARRAY> list;
    PROPARRAY prop;
    prop.id = 1;
    prop.value = 100;
    prop.flags = 0;

    list.Add(prop);
    list.Clear();
    EXPECT_EQ(list.GetCount(), 0u);
}

// Test Param
TEST(ParamTest, DefaultConstructor) {
    Param param;
    EXPECT_EQ(param.GetCount(), 0u);
}

TEST(ParamTest, Add) {
    Param param;
    param.Add("name", "value");
    EXPECT_EQ(param.GetCount(), 1u);
}

TEST(ParamTest, Get) {
    Param param;
    param.Add("name", "value");
    const char* value = param.Get("name");
    EXPECT_NE(value, nullptr);
    EXPECT_STREQ(value, "value");
}

TEST(ParamTest, GetNotFound) {
    Param param;
    const char* value = param.Get("nonexistent");
    EXPECT_EQ(value, nullptr);
}

TEST(ParamTest, GetInt) {
    Param param;
    param.Add("port", "8080");
    int value = param.GetInt("port");
    EXPECT_EQ(value, 8080);
}

TEST(ParamTest, GetIntDefault) {
    Param param;
    int value = param.GetInt("port", 80);
    EXPECT_EQ(value, 80);
}

TEST(ParamTest, GetFloat) {
    Param param;
    param.Add("scale", "1.5");
    float value = param.GetFloat("scale");
    EXPECT_FLOAT_EQ(value, 1.5f);
}

TEST(ParamTest, GetFloatDefault) {
    Param param;
    float value = param.GetFloat("scale", 2.0f);
    EXPECT_FLOAT_EQ(value, 2.0f);
}

TEST(ParamTest, Has) {
    Param param;
    param.Add("name", "value");
    EXPECT_TRUE(param.Has("name"));
    EXPECT_FALSE(param.Has("nonexistent"));
}

TEST(ParamTest, Remove) {
    Param param;
    param.Add("name", "value");
    EXPECT_TRUE(param.Has("name"));

    param.Remove("name");
    EXPECT_FALSE(param.Has("name"));
}

TEST(ParamTest, Clear) {
    Param param;
    param.Add("name1", "value1");
    param.Add("name2", "value2");
    param.Clear();
    EXPECT_EQ(param.GetCount(), 0u);
}

TEST(ParamTest, ParseString) {
    Param param;
    param.ParseString("name=value port=8080");
    EXPECT_EQ(param.GetCount(), 2u);
    EXPECT_STREQ(param.Get("name"), "value");
    EXPECT_STREQ(param.Get("port"), "8080");
}

TEST(ParamTest, ParseStringQuoted) {
    Param param;
    param.ParseString("name=\"hello world\"");
    EXPECT_STREQ(param.Get("name"), "hello world");
}
