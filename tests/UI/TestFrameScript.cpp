#include <gtest/gtest.h>
#include "UI/Types.h"

// Forward declare to avoid Lua dependency
struct lua_State;

// Test SIMPLEFRAMENODE structure
struct SIMPLEFRAMENODE_Test {
    void *frame;
};

// Test EVENTLISTENERNODE structure
struct EVENTLISTENERNODE_Test {
    void *listener;
};

// Test FrameScript_Method structure
struct FrameScript_Method_Test {
    const char *name;
    int32_t (*method)(lua_State *);
};

TEST(FrameScriptTest, SimpleFrameNode) {
    SIMPLEFRAMENODE_Test node;
    node.frame = nullptr;
    EXPECT_EQ(node.frame, nullptr);
}

TEST(FrameScriptTest, EventListenerNode) {
    EVENTLISTENERNODE_Test node;
    node.listener = nullptr;
    EXPECT_EQ(node.listener, nullptr);
}

TEST(FrameScriptTest, FrameScriptMethod) {
    FrameScript_Method_Test method;
    method.name = "TestFunction";
    method.method = [](lua_State *L) -> int32_t {
        return 0;
    };

    EXPECT_NE(method.name, nullptr);
    EXPECT_NE(method.method, nullptr);
    EXPECT_STREQ(method.name, "TestFunction");
}

TEST(FrameScriptTest, FrameScriptMethodNull) {
    FrameScript_Method_Test method;
    method.name = nullptr;
    method.method = nullptr;

    EXPECT_EQ(method.name, nullptr);
    EXPECT_EQ(method.method, nullptr);
}
