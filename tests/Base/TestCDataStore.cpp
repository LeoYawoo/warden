#include <gtest/gtest.h>
#include "Base/CDataStore.h"

TEST(CDataStoreTest, DefaultConstructor) {
    CDataStore ds;
    EXPECT_TRUE(ds.IsEmpty());
    EXPECT_EQ(ds.GetSize(), 0u);
    EXPECT_EQ(ds.GetCapacity(), 0u);
    EXPECT_EQ(ds.Tell(), 0u);
}

TEST(CDataStoreTest, Write) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3, 4, 5};

    EXPECT_TRUE(ds.Write(data, sizeof(data)));
    EXPECT_EQ(ds.GetSize(), 5u);
    EXPECT_FALSE(ds.IsEmpty());
}

TEST(CDataStoreTest, WriteMultiple) {
    CDataStore ds;
    uint8_t data1[] = {1, 2, 3};
    uint8_t data2[] = {4, 5, 6};

    ds.Write(data1, sizeof(data1));
    ds.Write(data2, sizeof(data2));

    EXPECT_EQ(ds.GetSize(), 6u);
}

TEST(CDataStoreTest, Read) {
    CDataStore ds;
    uint8_t writeData[] = {10, 20, 30, 40, 50};
    ds.Write(writeData, sizeof(writeData));

    uint8_t readData[5] = {0};
    EXPECT_TRUE(ds.Read(readData, sizeof(readData)));

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(readData[i], writeData[i]);
    }
    EXPECT_EQ(ds.Tell(), 5u);
}

TEST(CDataStoreTest, ReadBeyondSize) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3};
    ds.Write(data, sizeof(data));

    uint8_t readData[10] = {0};
    EXPECT_FALSE(ds.Read(readData, 10));
}

TEST(CDataStoreTest, Skip) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3, 4, 5};
    ds.Write(data, sizeof(data));

    EXPECT_TRUE(ds.Skip(2));
    EXPECT_EQ(ds.Tell(), 2u);

    uint8_t readData[3] = {0};
    EXPECT_TRUE(ds.Read(readData, 3));
    EXPECT_EQ(readData[0], 3);
}

TEST(CDataStoreTest, Seek) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3, 4, 5};
    ds.Write(data, sizeof(data));

    EXPECT_TRUE(ds.Seek(3));
    EXPECT_EQ(ds.Tell(), 3u);

    EXPECT_FALSE(ds.Seek(10));  // Beyond size
}

TEST(CDataStoreTest, Remaining) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3, 4, 5};
    ds.Write(data, sizeof(data));

    ds.Skip(2);
    EXPECT_EQ(ds.Remaining(), 3u);
}

TEST(CDataStoreTest, CanRead) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3, 4, 5};
    ds.Write(data, sizeof(data));

    EXPECT_TRUE(ds.CanRead(5));
    EXPECT_FALSE(ds.CanRead(6));
}

TEST(CDataStoreTest, Clear) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3};
    ds.Write(data, sizeof(data));

    ds.Destroy();
    EXPECT_TRUE(ds.IsEmpty());
    EXPECT_EQ(ds.GetSize(), 0u);
    EXPECT_EQ(ds.Tell(), 0u);
}

TEST(CDataStoreTest, Reset) {
    CDataStore ds;
    uint8_t data[] = {1, 2, 3};
    ds.Write(data, sizeof(data));
    ds.Skip(2);

    ds.Reset();
    EXPECT_EQ(ds.Tell(), 0u);
    EXPECT_EQ(ds.GetSize(), 0u);  // Reset clears size
}

TEST(CDataStoreTest, WriteEmpty) {
    CDataStore ds;
    EXPECT_FALSE(ds.Write(nullptr, 10));
    EXPECT_FALSE(ds.Write(nullptr, 0));
}

TEST(CDataStoreTest, ReadEmpty) {
    CDataStore ds;
    uint8_t data[10] = {0};
    EXPECT_FALSE(ds.Read(data, 10));
}

TEST(CDataStoreTest, LargeWrite) {
    CDataStore ds;
    std::vector<uint8_t> largeData(10000, 42);
    EXPECT_TRUE(ds.Write(largeData.data(), largeData.size()));
    EXPECT_EQ(ds.GetSize(), 10000u);
}

TEST(CDataStoreTest, MultipleOperations) {
    CDataStore ds;

    // Write some data
    uint8_t data1[] = {1, 2, 3};
    ds.Write(data1, sizeof(data1));

    // Read it back
    uint8_t readData[3] = {0};
    ds.Read(readData, sizeof(readData));
    EXPECT_EQ(readData[0], 1);
    EXPECT_EQ(readData[1], 2);
    EXPECT_EQ(readData[2], 3);

    // Skip and write more
    ds.Skip(1);
    uint8_t data2[] = {4, 5};
    ds.Write(data2, sizeof(data2));

    EXPECT_EQ(ds.GetSize(), 5u);  // 3 + 2 = 5
}
