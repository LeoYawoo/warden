#include <gtest/gtest.h>
#include "Glue/CGlueMgr.h"

TEST(CGlueMgrTest, GLUE_IDLE_STATEValues) {
    EXPECT_EQ(CGlueMgr::IDLE_NONE, 0);
    EXPECT_EQ(CGlueMgr::IDLE_LOGIN_SERVER_LOGIN, 1);
    EXPECT_EQ(CGlueMgr::IDLE_ACCOUNT_LOGIN, 2);
    EXPECT_EQ(CGlueMgr::NUM_IDLE_STATES, 14);
}

TEST(CGlueMgrTest, GetIdleStateName) {
    EXPECT_STREQ(CGlueMgr::GetIdleStateName(CGlueMgr::IDLE_NONE), "NONE");
    EXPECT_STREQ(CGlueMgr::GetIdleStateName(CGlueMgr::IDLE_LOGIN_SERVER_LOGIN), "LOGIN_SERVER_LOGIN");
    EXPECT_STREQ(CGlueMgr::GetIdleStateName(CGlueMgr::IDLE_ACCOUNT_LOGIN), "ACCOUNT_LOGIN");
    EXPECT_STREQ(CGlueMgr::GetIdleStateName(static_cast<CGlueMgr::GLUE_IDLE_STATE>(100)), "UNKNOWN");
}

TEST(CGlueMgrTest, IsIdleStateValid) {
    EXPECT_TRUE(CGlueMgr::IsIdleStateValid(CGlueMgr::IDLE_NONE));
    EXPECT_TRUE(CGlueMgr::IsIdleStateValid(CGlueMgr::IDLE_ACCOUNT_LOGIN));
    EXPECT_FALSE(CGlueMgr::IsIdleStateValid(static_cast<CGlueMgr::GLUE_IDLE_STATE>(100)));
}

TEST(CGlueMgrTest, StaticVariablesExist) {
    // Just verify the static variables exist
    EXPECT_TRUE(&CGlueMgr::m_acceptedEULA != nullptr);
    EXPECT_TRUE(&CGlueMgr::m_authenticated != nullptr);
    EXPECT_TRUE(&CGlueMgr::m_idleState != nullptr);
}

TEST(CGlueMgrTest, LOGIN_STATEFromNet) {
    // Verify LOGIN_STATE values from Net/Types.h
    EXPECT_EQ(LOGIN_STATE_INITIALIZED, 0);
    EXPECT_EQ(LOGIN_STATE_CONNECTING, 1);
    EXPECT_EQ(LOGIN_STATE_AUTHENTICATED, 4);
    EXPECT_EQ(LOGIN_STATE_DISCONNECTED, 16);
}

TEST(CGlueMgrTest, LOGIN_RESULTFromNet) {
    // Verify LOGIN_RESULT values from Net/Types.h
    EXPECT_EQ(LOGIN_OK, 0);
    EXPECT_EQ(LOGIN_FAILED, 11);
    EXPECT_EQ(LOGIN_BANNED, 13);
}
