#include <gtest/gtest.h>
#include "Base/MsgBuffer.h"

TEST(MsgBufferTest, DefaultConstructor) {
    MsgBuffer buf;
    EXPECT_TRUE(buf.IsEmpty());
    EXPECT_EQ(buf.GetSize(), 0u);
    EXPECT_EQ(buf.GetCapacity(), 0u);
    EXPECT_EQ(buf.Tell(), 0u);
}

TEST(MsgBufferTest, SizeConstructor) {
    MsgBuffer buf(1024);
    EXPECT_TRUE(buf.IsEmpty());
    EXPECT_EQ(buf.GetCapacity(), 1024u);
}

TEST(MsgBufferTest, Write) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3, 4, 5};

    EXPECT_TRUE(buf.Write(data, sizeof(data)));
    EXPECT_EQ(buf.GetSize(), 5u);
    EXPECT_FALSE(buf.IsEmpty());
}

TEST(MsgBufferTest, WriteMultiple) {
    MsgBuffer buf;
    uint8_t data1[] = {1, 2, 3};
    uint8_t data2[] = {4, 5, 6};

    buf.Write(data1, sizeof(data1));
    buf.Write(data2, sizeof(data2));

    EXPECT_EQ(buf.GetSize(), 6u);
}

TEST(MsgBufferTest, Read) {
    MsgBuffer buf;
    uint8_t writeData[] = {10, 20, 30, 40, 50};
    buf.Write(writeData, sizeof(writeData));

    uint8_t readData[5] = {0};
    EXPECT_TRUE(buf.Read(readData, sizeof(readData)));

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(readData[i], writeData[i]);
    }
    EXPECT_EQ(buf.Tell(), 5u);
}

TEST(MsgBufferTest, ReadBeyondSize) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3};
    buf.Write(data, sizeof(data));

    uint8_t readData[10] = {0};
    EXPECT_FALSE(buf.Read(readData, 10));
}

TEST(MsgBufferTest, Skip) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3, 4, 5};
    buf.Write(data, sizeof(data));

    EXPECT_TRUE(buf.Skip(2));
    EXPECT_EQ(buf.Tell(), 2u);

    uint8_t readData[3] = {0};
    EXPECT_TRUE(buf.Read(readData, 3));
    EXPECT_EQ(readData[0], 3);
}

TEST(MsgBufferTest, Seek) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3, 4, 5};
    buf.Write(data, sizeof(data));

    EXPECT_TRUE(buf.Seek(3));
    EXPECT_EQ(buf.Tell(), 3u);

    EXPECT_FALSE(buf.Seek(10));  // Beyond size
}

TEST(MsgBufferTest, Remaining) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3, 4, 5};
    buf.Write(data, sizeof(data));

    buf.Skip(2);
    EXPECT_EQ(buf.Remaining(), 3u);
}

TEST(MsgBufferTest, CanRead) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3, 4, 5};
    buf.Write(data, sizeof(data));

    EXPECT_TRUE(buf.CanRead(5));
    EXPECT_FALSE(buf.CanRead(6));
}

TEST(MsgBufferTest, Clear) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3};
    buf.Write(data, sizeof(data));

    buf.Clear();
    EXPECT_TRUE(buf.IsEmpty());
    EXPECT_EQ(buf.GetSize(), 0u);
    EXPECT_EQ(buf.Tell(), 0u);
}

TEST(MsgBufferTest, Reset) {
    MsgBuffer buf;
    uint8_t data[] = {1, 2, 3};
    buf.Write(data, sizeof(data));
    buf.Skip(2);

    buf.Reset();
    EXPECT_EQ(buf.Tell(), 0u);
    EXPECT_EQ(buf.GetSize(), 0u);  // Reset clears size
}

TEST(MsgBufferTest, WriteEmpty) {
    MsgBuffer buf;
    EXPECT_FALSE(buf.Write(nullptr, 10));
    EXPECT_FALSE(buf.Write(nullptr, 0));
}

TEST(MsgBufferTest, ReadEmpty) {
    MsgBuffer buf;
    uint8_t data[10] = {0};
    EXPECT_FALSE(buf.Read(data, 10));
}

TEST(MsgBufferTest, LargeWrite) {
    MsgBuffer buf;
    std::vector<uint8_t> largeData(10000, 42);
    EXPECT_TRUE(buf.Write(largeData.data(), largeData.size()));
    EXPECT_EQ(buf.GetSize(), 10000u);
}
