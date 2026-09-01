#include <gtest/gtest.h>
#include "Base/CDataStoreChunked.h"
#include "Base/CDataAllocator.h"
#include "Base/CDataRecycler.h"
#include "Base/FileCache.h"

// Test CDataStoreChunked
TEST(CDataStoreChunkedTest, DefaultConstructor) {
    CDataStoreChunked store;
    EXPECT_EQ(store.GetChunkCount(), 0u);
    EXPECT_EQ(store.GetChunkSize(), 4096u);
}

TEST(CDataStoreChunkedTest, SetChunkSize) {
    CDataStoreChunked store;
    store.SetChunkSize(8192);
    EXPECT_EQ(store.GetChunkSize(), 8192u);
}

TEST(CDataStoreChunkedTest, AllocateChunk) {
    CDataStoreChunked store;
    auto* chunk = store.AllocateChunk();
    EXPECT_NE(chunk, nullptr);
    EXPECT_EQ(store.GetChunkCount(), 1u);
}

TEST(CDataStoreChunkedTest, AllocateMultipleChunks) {
    CDataStoreChunked store;
    store.AllocateChunk();
    store.AllocateChunk();
    store.AllocateChunk();
    EXPECT_EQ(store.GetChunkCount(), 3u);
}

// Test CDataAllocator
TEST(CDataAllocatorTest, DefaultConstructor) {
    CDataAllocator allocator;
    EXPECT_EQ(allocator.GetTotalAllocated(), 0u);
    EXPECT_EQ(allocator.GetAllocationCount(), 0u);
}

TEST(CDataAllocatorTest, Allocate) {
    CDataAllocator allocator;
    void* ptr = allocator.Allocate(1024);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(allocator.GetAllocationCount(), 1u);
    allocator.Free(ptr);
}

TEST(CDataAllocatorTest, AllocateMultiple) {
    CDataAllocator allocator;
    void* ptr1 = allocator.Allocate(1024);
    void* ptr2 = allocator.Allocate(2048);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(allocator.GetAllocationCount(), 2u);
    allocator.Free(ptr1);
    allocator.Free(ptr2);
}

TEST(CDataAllocatorTest, Free) {
    CDataAllocator allocator;
    void* ptr = allocator.Allocate(1024);
    EXPECT_EQ(allocator.GetAllocationCount(), 1u);
    allocator.Free(ptr);
    EXPECT_EQ(allocator.GetAllocationCount(), 0u);
}

TEST(CDataAllocatorTest, Reset) {
    CDataAllocator allocator;
    allocator.Allocate(1024);
    allocator.Allocate(2048);
    allocator.Reset();
    EXPECT_EQ(allocator.GetAllocationCount(), 0u);
}

// Test CDataRecycler
TEST(CDataRecyclerTest, DefaultConstructor) {
    CDataRecycler recycler;
    EXPECT_EQ(recycler.GetTotalRecycled(), 0u);
    EXPECT_EQ(recycler.GetRecycledCount(), 0u);
}

TEST(CDataRecyclerTest, ReturnData) {
    CDataRecycler recycler;
    void* data = malloc(1024);
    recycler.ReturnData(data, 1024);
    EXPECT_EQ(recycler.GetRecycledCount(), 1u);
    EXPECT_EQ(recycler.GetTotalRecycled(), 1024u);
}

TEST(CDataRecyclerTest, Clear) {
    CDataRecycler recycler;
    void* data = malloc(1024);
    recycler.ReturnData(data, 1024);
    recycler.Clear();
    EXPECT_EQ(recycler.GetRecycledCount(), 0u);
    EXPECT_EQ(recycler.GetTotalRecycled(), 0u);
}

// Test FileCache
TEST(FileCacheTest, DefaultConstructor) {
    FileCache cache;
    EXPECT_FALSE(cache.IsOpen());
    EXPECT_EQ(cache.Tell(), 0);
}

TEST(FileCacheTest, OpenClose) {
    FileCache cache;
    // Note: This test requires a file to exist
    // For now, just test the state changes
    EXPECT_FALSE(cache.IsOpen());
}

TEST(FileCacheTest, Seek) {
    FileCache cache;
    // Test seek without open file
    EXPECT_FALSE(cache.Seek(100, SEEK_SET));
}

TEST(FileCacheTest, Tell) {
    FileCache cache;
    EXPECT_EQ(cache.Tell(), 0);
}
