#include <gtest/gtest.h>
#include "Event/EvtMessage.h"

TEST(EvtMessageTest, DefaultConstructor) {
    EvtMessage msg;
    EXPECT_EQ(msg.id, EVENT_ID_0);
    EXPECT_FALSE(msg.HasData());
}

TEST(EvtMessageTest, IdConstructor) {
    EvtMessage msg(EVENT_ID_KEYDOWN);
    EXPECT_EQ(msg.id, EVENT_ID_KEYDOWN);
    EXPECT_TRUE(msg.HasData());
}

TEST(EvtMessageTest, DataConstructor) {
    // Use a small data type that fits in 4 bytes
    uint32_t keyData = KEY_A;

    EvtMessage msg(EVENT_ID_KEYDOWN, &keyData, sizeof(keyData));
    EXPECT_EQ(msg.id, EVENT_ID_KEYDOWN);
    EXPECT_TRUE(msg.HasData());

    const uint32_t* retrieved = msg.GetData<uint32_t>();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(*retrieved, KEY_A);
}

TEST(EvtMessageTest, TemplateConstructor) {
    // Use a small data type that fits in 4 bytes
    int32_t sizeData = 800;

    EvtMessage msg(EVENT_ID_SIZE, sizeData);
    EXPECT_EQ(msg.id, EVENT_ID_SIZE);

    const int32_t* retrieved = msg.GetData<int32_t>();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(*retrieved, 800);
}

TEST(EvtMessageTest, Clear) {
    EvtMessage msg(EVENT_ID_KEYDOWN);
    EXPECT_TRUE(msg.HasData());

    msg.Clear();
    EXPECT_EQ(msg.id, EVENT_ID_0);
    EXPECT_FALSE(msg.HasData());
}

TEST(EvtMessageTest, GetDataMutable) {
    EvtMessage msg(EVENT_ID_SIZE);

    EVENT_DATA_SIZE* data = msg.GetData<EVENT_DATA_SIZE>();
    EXPECT_NE(data, nullptr);

    data->w = 1024;
    data->h = 768;

    const EVENT_DATA_SIZE* constData = msg.GetData<EVENT_DATA_SIZE>();
    EXPECT_EQ(constData->w, 1024);
    EXPECT_EQ(constData->h, 768);
}

TEST(EvtMessageTest, LargeDataTruncation) {
    // Test that data larger than 4 bytes is truncated
    char largeData[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    EvtMessage msg(EVENT_ID_NET_DATA, largeData, sizeof(largeData));

    // Only first 4 bytes should be copied
    EXPECT_EQ(msg.data[0], 1);
    EXPECT_EQ(msg.data[1], 2);
    EXPECT_EQ(msg.data[2], 3);
    EXPECT_EQ(msg.data[3], 4);
}
