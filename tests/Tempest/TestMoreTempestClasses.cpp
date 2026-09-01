#include <gtest/gtest.h>
#include "Tempest/CDynParms.h"
#include "Tempest/CPriorityQ.h"
#include "Tempest/CPresenceSys.h"
#include "Tempest/CPresenceSysTagged.h"

using namespace Tempest;

// Test CDynParms
TEST(CDynParmsTest, DefaultConstructor) {
    CDynParms parms;
    EXPECT_EQ(parms.GetInitialSize(), 0u);
    EXPECT_EQ(parms.GetGrowSize(), 0u);
    EXPECT_EQ(parms.GetMaxSize(), 0u);
}

TEST(CDynParmsTest, ParameterizedConstructor) {
    CDynParms parms(1024, 256, 4096);
    EXPECT_EQ(parms.GetInitialSize(), 1024u);
    EXPECT_EQ(parms.GetGrowSize(), 256u);
    EXPECT_EQ(parms.GetMaxSize(), 4096u);
}

TEST(CDynParmsTest, SetInitialSize) {
    CDynParms parms;
    parms.SetInitialSize(2048);
    EXPECT_EQ(parms.GetInitialSize(), 2048u);
}

TEST(CDynParmsTest, SetGrowSize) {
    CDynParms parms;
    parms.SetGrowSize(512);
    EXPECT_EQ(parms.GetGrowSize(), 512u);
}

TEST(CDynParmsTest, SetMaxSize) {
    CDynParms parms;
    parms.SetMaxSize(8192);
    EXPECT_EQ(parms.GetMaxSize(), 8192u);
}

// Test CPriorityQ
TEST(CPriorityQTest, DefaultConstructor) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_EQ(queue.GetCount(), 0u);
}

TEST(CPriorityQTest, Enqueue) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    queue.Enqueue(10);
    EXPECT_FALSE(queue.IsEmpty());
    EXPECT_EQ(queue.GetCount(), 1u);
}

TEST(CPriorityQTest, EnqueueMultiple) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    EXPECT_EQ(queue.GetCount(), 3u);
}

TEST(CPriorityQTest, Dequeue) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);

    int item = queue.Dequeue();
    EXPECT_EQ(item, 30);  // Highest priority first
    EXPECT_EQ(queue.GetCount(), 2u);
}

TEST(CPriorityQTest, DequeueAll) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    queue.Enqueue(10);
    queue.Enqueue(20);

    queue.Dequeue();
    queue.Dequeue();
    EXPECT_TRUE(queue.IsEmpty());
}

TEST(CPriorityQTest, DiscardAll) {
    CDynParms parms(10, 5, 100);
    CPriorityQ<int> queue(parms);
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.DiscardAll();
    EXPECT_TRUE(queue.IsEmpty());
}

// Test CPresenceSys
TEST(CPresenceSysTest, DefaultConstructor) {
    CPresenceSys presence;
    EXPECT_FALSE(presence.IsInitialized());
    EXPECT_EQ(presence.GetSystemId(), 0);
}

TEST(CPresenceSysTest, Initialize) {
    CPresenceSys presence;
    presence.Initialize();
    EXPECT_TRUE(presence.IsInitialized());
}

TEST(CPresenceSysTest, Shutdown) {
    CPresenceSys presence;
    presence.Initialize();
    presence.Shutdown();
    EXPECT_FALSE(presence.IsInitialized());
}

TEST(CPresenceSysTest, SetSystemId) {
    CPresenceSys presence;
    presence.SetSystemId(42);
    EXPECT_EQ(presence.GetSystemId(), 42);
}

// Test CPresenceSysTagged
TEST(CPresenceSysTaggedTest, DefaultConstructor) {
    CPresenceSysTagged presence;
    EXPECT_FALSE(presence.IsTagged());
    EXPECT_EQ(presence.GetTag(), -1);
}

TEST(CPresenceSysTaggedTest, SetTag) {
    CPresenceSysTagged presence;
    presence.SetTag(100);
    EXPECT_TRUE(presence.IsTagged());
    EXPECT_EQ(presence.GetTag(), 100);
}

TEST(CPresenceSysTaggedTest, SetTagNegative) {
    CPresenceSysTagged presence;
    presence.SetTag(-5);
    EXPECT_FALSE(presence.IsTagged());
}
