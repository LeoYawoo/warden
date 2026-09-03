#include <gtest/gtest.h>
#include "World/WorldCampaign.h"
#include "World/WorldLoad.h"

// Test WorldCampaign
TEST(WorldCampaignTest, DefaultConstructor) {
    WorldCampaign campaign;
    EXPECT_FALSE(campaign.IsInitialized());
    EXPECT_TRUE(campaign.IsVisible());
    EXPECT_EQ(campaign.GetMissionCount(), 0u);
}

TEST(WorldCampaignTest, Initialize) {
    WorldCampaign campaign;
    EXPECT_TRUE(campaign.Initialize());
    EXPECT_TRUE(campaign.IsInitialized());
}

TEST(WorldCampaignTest, SetCampaignName) {
    WorldCampaign campaign;
    campaign.SetCampaignName("Human Campaign");
    EXPECT_STREQ(campaign.GetCampaignName(), "Human Campaign");
}

TEST(WorldCampaignTest, SetCampaignDescription) {
    WorldCampaign campaign;
    campaign.SetCampaignDescription("The rise of the Alliance");
    EXPECT_STREQ(campaign.GetCampaignDescription(), "The rise of the Alliance");
}

TEST(WorldCampaignTest, AddMission) {
    WorldCampaign campaign;
    campaign.Initialize();
    campaign.AddMission("Mission 1", 1);
    campaign.AddMission("Mission 2", 2);
    EXPECT_EQ(campaign.GetMissionCount(), 2u);
    EXPECT_STREQ(campaign.GetMissionName(0), "Mission 1");
    EXPECT_EQ(campaign.GetMissionId(0), 1);
}

TEST(WorldCampaignTest, RemoveMission) {
    WorldCampaign campaign;
    campaign.Initialize();
    campaign.AddMission("Mission 1", 1);
    campaign.AddMission("Mission 2", 2);
    campaign.RemoveMission(1);
    EXPECT_EQ(campaign.GetMissionCount(), 1u);
}

TEST(WorldCampaignTest, SetVisible) {
    WorldCampaign campaign;
    campaign.SetVisible(false);
    EXPECT_FALSE(campaign.IsVisible());
}

// Test WorldLoad
TEST(WorldLoadTest, DefaultConstructor) {
    WorldLoad load;
    EXPECT_FALSE(load.IsInitialized());
    EXPECT_FALSE(load.IsLoading());
    EXPECT_FLOAT_EQ(load.GetProgress(), 0.0f);
}

TEST(WorldLoadTest, Initialize) {
    WorldLoad load;
    EXPECT_TRUE(load.Initialize());
    EXPECT_TRUE(load.IsInitialized());
}

TEST(WorldLoadTest, SetMapFile) {
    WorldLoad load;
    load.SetMapFile("test.w3m");
    EXPECT_STREQ(load.GetMapFile(), "test.w3m");
}

TEST(WorldLoadTest, LoadMap) {
    WorldLoad load;
    load.Initialize();
    EXPECT_TRUE(load.LoadMap("test.w3m"));
    EXPECT_STREQ(load.GetMapFile(), "test.w3m");
}

TEST(WorldLoadTest, CancelLoad) {
    WorldLoad load;
    load.Initialize();
    load.SetLoading(true);
    load.CancelLoad();
    EXPECT_FALSE(load.IsLoading());
}

TEST(WorldLoadTest, SetProgress) {
    WorldLoad load;
    load.SetProgress(0.5f);
    EXPECT_FLOAT_EQ(load.GetProgress(), 0.5f);
}
