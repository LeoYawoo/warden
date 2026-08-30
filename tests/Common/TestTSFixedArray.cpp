#include <gtest/gtest.h>
#include "Common/TSFixedArray.h"

TEST(TSFixedArrayTest, DefaultConstructor) {
    TSFixedArray<int> arr;
    EXPECT_EQ(arr.Count(), 0u);
    EXPECT_EQ(arr.Ptr(), nullptr);
}

TEST(TSFixedArrayTest, SetCount) {
    TSFixedArray<int> arr;
    arr.SetCount(10);
    EXPECT_EQ(arr.Count(), 10u);
    EXPECT_NE(arr.Ptr(), nullptr);
}

TEST(TSFixedArrayTest, Set) {
    TSFixedArray<int> arr;
    int data[] = {1, 2, 3, 4, 5};
    arr.Set(5, data);
    EXPECT_EQ(arr.Count(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(TSFixedArrayTest, Clear) {
    TSFixedArray<int> arr;
    arr.SetCount(10);
    arr.Clear();
    EXPECT_EQ(arr.Count(), 0u);
}

TEST(TSFixedArrayTest, OperatorAssignment) {
    TSFixedArray<int> arr1;
    TSFixedArray<int> arr2;

    int data[] = {1, 2, 3};
    arr1.Set(3, data);

    arr2 = arr1;

    EXPECT_EQ(arr2.Count(), 3u);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[2], 3);
}

TEST(TSFixedArrayTest, OperatorIndex) {
    TSFixedArray<int> arr;
    arr.SetCount(5);

    arr[0] = 10;
    arr[4] = 50;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[4], 50);
}

TEST(TSFixedArrayTest, Top) {
    TSFixedArray<int> arr;
    arr.SetCount(5);

    arr[4] = 42;

    int *top = arr.Top();
    EXPECT_NE(top, nullptr);
    EXPECT_EQ(*top, 42);
}

TEST(TSFixedArrayTest, TopEmpty) {
    TSFixedArray<int> arr;
    EXPECT_EQ(arr.Top(), nullptr);
}

TEST(TSFixedArrayTest, Count) {
    TSFixedArray<int> arr;
    EXPECT_EQ(arr.Count(), 0u);

    arr.SetCount(10);
    EXPECT_EQ(arr.Count(), 10u);

    arr.Clear();
    EXPECT_EQ(arr.Count(), 0u);
}

TEST(TSFixedArrayTest, Ptr) {
    TSFixedArray<int> arr;
    EXPECT_EQ(arr.Ptr(), nullptr);

    arr.SetCount(5);
    EXPECT_NE(arr.Ptr(), nullptr);
}

TEST(TSFixedArrayTest, ReallocData) {
    TSFixedArray<int> arr;
    arr.SetCount(5);
    arr[0] = 42;

    arr.ReallocData(10);
    EXPECT_EQ(arr.Count(), 5u);
    EXPECT_EQ(arr[0], 42);
}

TEST(TSFixedArrayTest, ReallocAndClearData) {
    TSFixedArray<int> arr;
    arr.SetCount(5);
    arr[0] = 42;

    arr.ReallocAndClearData(10);
    EXPECT_EQ(arr.Count(), 0u);
}
