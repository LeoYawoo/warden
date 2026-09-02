#include <gtest/gtest.h>
#include "Net/NetClient.h"
#include "Net/NetCommon.h"
#include "Net/NetProvider.h"
#include "Net/NetProviderBNET.h"
#include "Net/NetProviderLOOP.h"
#include "Net/NetProviderLTCP.h"
#include "Net/NetRouter.h"

// Test NetClient
TEST(NetClientTest, DefaultConstructor) {
    NetClient client;
    EXPECT_FALSE(client.IsConnected());
    EXPECT_EQ(client.GetState(), NetClient::DISCONNECTED);
}

TEST(NetClientTest, Connect) {
    NetClient client;
    EXPECT_TRUE(client.Connect("127.0.0.1", 8080));
    EXPECT_TRUE(client.IsConnected());
    EXPECT_EQ(client.GetState(), NetClient::CONNECTED);
}

TEST(NetClientTest, Disconnect) {
    NetClient client;
    client.Connect("127.0.0.1", 8080);
    client.Disconnect();
    EXPECT_FALSE(client.IsConnected());
}

TEST(NetClientTest, GetHostPort) {
    NetClient client;
    client.Connect("192.168.1.1", 12345);
    EXPECT_STREQ(client.GetHost(), "192.168.1.1");
    EXPECT_EQ(client.GetPort(), 12345);
}

// Test NetCommon
TEST(NetCommonTest, HostToNetwork32) {
    EXPECT_EQ(NetCommon::HostToNetwork32(0x01020304), 0x04030201u);
}

TEST(NetCommonTest, HostToNetwork16) {
    EXPECT_EQ(NetCommon::HostToNetwork16(0x0102), 0x0201u);
}

TEST(NetCommonTest, FormatIP) {
    char str[16];
    NetCommon::FormatIP(0xC0A80101, str, sizeof(str));
    EXPECT_STREQ(str, "192.168.1.1");
}

TEST(NetCommonTest, CalculateChecksum) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    uint16_t checksum = NetCommon::CalculateChecksum(data, sizeof(data));
    EXPECT_NE(checksum, 0);
}

// Test NetProvider
TEST(NetProviderTest, DefaultConstructor) {
    NetProvider provider;
    EXPECT_EQ(provider.GetProviderType(), NetProvider::PROVIDER_UNKNOWN);
}

TEST(NetProviderTest, Initialize) {
    NetProvider provider;
    EXPECT_TRUE(provider.Initialize());
}

// Test NetProviderBNET
TEST(NetProviderBNETTest, DefaultConstructor) {
    NetProviderBNET provider;
    EXPECT_EQ(provider.GetProviderType(), NetProvider::PROVIDER_BNET);
    EXPECT_STREQ(provider.GetProviderName(), "Battle.net");
}

TEST(NetProviderBNETTest, Connect) {
    NetProviderBNET provider;
    EXPECT_TRUE(provider.Connect("bnet.example.com", 6112));
    EXPECT_TRUE(provider.IsConnected());
}

// Test NetProviderLOOP
TEST(NetProviderLOOPTest, DefaultConstructor) {
    NetProviderLOOP provider;
    EXPECT_EQ(provider.GetProviderType(), NetProvider::PROVIDER_LOOP);
    EXPECT_STREQ(provider.GetProviderName(), "Loopback");
}

TEST(NetProviderLOOPTest, Connect) {
    NetProviderLOOP provider;
    EXPECT_TRUE(provider.Connect("localhost", 0));
    EXPECT_TRUE(provider.IsConnected());
}

TEST(NetProviderLOOPTest, SendReceive) {
    NetProviderLOOP provider;
    provider.Connect("localhost", 0);

    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_TRUE(provider.Send(data, sizeof(data)));

    uint8_t buffer[4];
    uint32_t bytesRead;
    EXPECT_TRUE(provider.Receive(buffer, sizeof(buffer), &bytesRead));
    EXPECT_EQ(bytesRead, 4u);
    EXPECT_EQ(memcmp(data, buffer, 4), 0);
}

// Test NetProviderLTCP
TEST(NetProviderLTCPTest, DefaultConstructor) {
    NetProviderLTCP provider;
    EXPECT_EQ(provider.GetProviderType(), NetProvider::PROVIDER_LTCP);
    EXPECT_STREQ(provider.GetProviderName(), "LAN TCP");
}

TEST(NetProviderLTCPTest, Connect) {
    NetProviderLTCP provider;
    EXPECT_TRUE(provider.Connect("192.168.1.100", 6112));
    EXPECT_TRUE(provider.IsConnected());
}

// Test NetRouter
TEST(NetRouterTest, DefaultConstructor) {
    NetRouter router;
    EXPECT_FALSE(router.IsInitialized());
    EXPECT_EQ(router.GetProviderCount(), 0u);
}

TEST(NetRouterTest, Initialize) {
    NetRouter router;
    EXPECT_TRUE(router.Initialize());
    EXPECT_TRUE(router.IsInitialized());
}

TEST(NetRouterTest, AddProvider) {
    NetRouter router;
    NetProviderBNET provider;
    router.AddProvider(&provider);
    EXPECT_EQ(router.GetProviderCount(), 1u);
}

TEST(NetRouterTest, RemoveProvider) {
    NetRouter router;
    NetProviderBNET provider;
    router.AddProvider(&provider);
    router.RemoveProvider(&provider);
    EXPECT_EQ(router.GetProviderCount(), 0u);
}

TEST(NetRouterTest, GetProvider) {
    NetRouter router;
    NetProviderBNET provider;
    router.AddProvider(&provider);
    EXPECT_EQ(router.GetProvider(0), &provider);
    EXPECT_EQ(router.GetProvider(1), nullptr);
}

TEST(NetRouterTest, Route) {
    NetRouter router;
    NetProviderBNET provider;
    provider.Connect("test", 80);
    router.AddProvider(&provider);

    uint8_t data[] = {0x01, 0x02};
    EXPECT_TRUE(router.Route(data, sizeof(data)));
}
