#include <gtest/gtest.h>
#include "Base/CDataStore.h"

TEST(CDataStoreTest, DefaultConstructor) {
    CDataStore ds;
    EXPECT_EQ(ds.Size(), 0u);
}

TEST(CDataStoreTest, SetSize) {
    CDataStore ds;
    ds.SetSize(1000);
    EXPECT_EQ(ds.Size(), 1000u);
}

TEST(CDataStoreTest, Reset) {
    CDataStore ds;
    ds.SetSize(100);
    ds.Reset();
    EXPECT_EQ(ds.Size(), 0u);
}

TEST(CDataStoreTest, IsRead) {
    CDataStore ds;
    EXPECT_TRUE(ds.IsRead());
}

TEST(CDataStoreTest, GetBufferParams) {
    CDataStore ds;
    ds.SetSize(100);

    const void* data = nullptr;
    uint32_t size = 0;
    uint32_t alloc = 0;

    ds.GetBufferParams(&data, &size, &alloc);
    EXPECT_NE(data, nullptr);
    EXPECT_EQ(size, 100u);
}
