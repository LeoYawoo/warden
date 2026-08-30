#include <gtest/gtest.h>
#include "Common/TSGrowableArray.h"

TEST(TSGrowableArrayTest, DefaultConstructor) {
    TSGrowableArray<int> arr;
    EXPECT_EQ(arr.Count(), 0u);
}

TEST(TSGrowableArrayTest, SetCount) {
    TSGrowableArray<int> arr;
    arr.SetCount(10);
    EXPECT_EQ(arr.Count(), 10u);
}

TEST(TSGrowableArrayTest, Add) {
    TSGrowableArray<int> arr;
    int data[] = {1, 2, 3, 4, 5};
    arr.Add(5, data);
    EXPECT_EQ(arr.Count(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(TSGrowableArrayTest, Reserve) {
    TSGrowableArray<int> arr;
    arr.Reserve(100, 1);
    EXPECT_GE(arr.Reserved(), 100u);
}

TEST(TSGrowableArrayTest, GrowToFit) {
    TSGrowableArray<int> arr;
    arr.GrowToFit(10, 1);
    EXPECT_GT(arr.Count(), 10u);
    EXPECT_EQ(arr[10], 0);  // Should be zeroed
}

TEST(TSGrowableArrayTest, New) {
    TSGrowableArray<int> arr;
    int *item = arr.New();
    EXPECT_NE(item, nullptr);
    EXPECT_EQ(arr.Count(), 1u);
}

TEST(TSGrowableArrayTest, CalcChunkSize) {
    TSGrowableArray<int> arr;
    // Test various chunk size calculations
    uint32_t chunk1 = arr.CalcChunkSize(1);
    uint32_t chunk2 = arr.CalcChunkSize(8);
    uint32_t chunk3 = arr.CalcChunkSize(1000);

    EXPECT_GT(chunk1, 0u);
    EXPECT_GT(chunk2, 0u);
    EXPECT_GT(chunk3, 0u);
}

TEST(TSGrowableArrayTest, RoundToChunk) {
    TSGrowableArray<int> arr;
    uint32_t result = arr.RoundToChunk(10, 4);
    EXPECT_EQ(result, 12u);  // Rounded up to next multiple of 4

    result = arr.RoundToChunk(8, 4);
    EXPECT_EQ(result, 8u);  // Already a multiple of 4
}

TEST(TSGrowableArrayTest, MultipleAdds) {
    TSGrowableArray<int> arr;
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};

    arr.Add(3, data1);
    arr.Add(2, data2);

    EXPECT_EQ(arr.Count(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST(TSGrowableArrayTest, ClearAndReuse) {
    TSGrowableArray<int> arr;
    arr.SetCount(5);
    arr.Clear();
    EXPECT_EQ(arr.Count(), 0u);

    arr.SetCount(3);
    EXPECT_EQ(arr.Count(), 3u);
}
