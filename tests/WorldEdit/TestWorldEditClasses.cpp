#include <gtest/gtest.h>
#include "WorldEdit/CTerrain.h"
#include "WorldEdit/CTerrainClickEvent.h"
#include "WorldEdit/CWeatherArea.h"
#include "WorldEdit/CRegion.h"

// Test CTerrain
TEST(CTerrainTest, DefaultConstructor) {
    CTerrain terrain;
    EXPECT_EQ(terrain.GetWidth(), 0);
    EXPECT_EQ(terrain.GetHeight(), 0);
    EXPECT_EQ(terrain.GetTileSize(), 0);
}

TEST(CTerrainTest, Initialize) {
    CTerrain terrain;
    terrain.Initialize(64, 64, 128);
    EXPECT_EQ(terrain.GetWidth(), 64);
    EXPECT_EQ(terrain.GetHeight(), 64);
    EXPECT_EQ(terrain.GetTileSize(), 128);
}

TEST(CTerrainTest, SetGetHeight) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    terrain.SetHeight(5, 5, 100.0f);
    EXPECT_FLOAT_EQ(terrain.GetHeight(5, 5), 100.0f);
}

TEST(CTerrainTest, SetGetFlags) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    terrain.SetFlags(3, 3, 0xFF);
    EXPECT_EQ(terrain.GetFlags(3, 3), 0xFFu);
}

TEST(CTerrainTest, SetGetWater) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    EXPECT_FALSE(terrain.IsWater(2, 2));
    terrain.SetWater(2, 2, true);
    EXPECT_TRUE(terrain.IsWater(2, 2));
}

TEST(CTerrainTest, InBounds) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    EXPECT_TRUE(terrain.InBounds(50.0f, 50.0f));
    EXPECT_FALSE(terrain.InBounds(2000.0f, 50.0f));
}

TEST(CTerrainTest, InBoundsInt) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    EXPECT_TRUE(terrain.InBoundsInt(5, 5));
    EXPECT_FALSE(terrain.InBoundsInt(15, 5));
}

TEST(CTerrainTest, Shutdown) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);
    terrain.Shutdown();
    EXPECT_EQ(terrain.GetWidth(), 0);
}

// Test CTerrainClickEvent
TEST(CTerrainClickEventTest, Constructor) {
    CTerrainClickEvent event(100);
    EXPECT_TRUE(event.IsValid());
    EXPECT_EQ(event.GetClickX(), 0.0f);
    EXPECT_EQ(event.GetClickY(), 0.0f);
}

TEST(CTerrainClickEventTest, SetClickPosition) {
    CTerrainClickEvent event(100);
    event.SetClickPosition(10.0f, 20.0f);
    EXPECT_FLOAT_EQ(event.GetClickX(), 10.0f);
    EXPECT_FLOAT_EQ(event.GetClickY(), 20.0f);
}

TEST(CTerrainClickEventTest, SetTerrain) {
    CTerrainClickEvent event(100);
    CTerrain terrain;
    event.SetTerrain(&terrain);
    EXPECT_EQ(event.GetTerrain(), &terrain);
}

// Test CWeatherArea
TEST(CWeatherAreaTest, DefaultConstructor) {
    CWeatherArea area;
    EXPECT_EQ(area.GetAreaId(), 0);
    EXPECT_FALSE(area.IsActive());
    EXPECT_EQ(area.GetWeatherType(), 0);
}

TEST(CWeatherAreaTest, SetAreaId) {
    CWeatherArea area;
    area.SetAreaId(42);
    EXPECT_EQ(area.GetAreaId(), 42);
}

TEST(CWeatherAreaTest, SetAreaName) {
    CWeatherArea area;
    area.SetAreaName("RainArea");
    EXPECT_STREQ(area.GetAreaName(), "RainArea");
}

TEST(CWeatherAreaTest, SetBounds) {
    CWeatherArea area;
    area.SetBounds(10.0f, 20.0f, 100.0f, 200.0f);
    EXPECT_FLOAT_EQ(area.GetMinX(), 10.0f);
    EXPECT_FLOAT_EQ(area.GetMinY(), 20.0f);
    EXPECT_FLOAT_EQ(area.GetMaxX(), 100.0f);
    EXPECT_FLOAT_EQ(area.GetMaxY(), 200.0f);
}

TEST(CWeatherAreaTest, SetActive) {
    CWeatherArea area;
    area.SetActive(true);
    EXPECT_TRUE(area.IsActive());
}

TEST(CWeatherAreaTest, SetWeatherType) {
    CWeatherArea area;
    area.SetWeatherType(3);
    EXPECT_EQ(area.GetWeatherType(), 3);
}

// Test CRegion
TEST(CRegionTest, DefaultConstructor) {
    CRegion region;
    EXPECT_EQ(region.GetRegionId(), 0);
    EXPECT_TRUE(region.IsEnabled());
    EXPECT_TRUE(region.IsVisible());
}

TEST(CRegionTest, SetRegionId) {
    CRegion region;
    region.SetRegionId(10);
    EXPECT_EQ(region.GetRegionId(), 10);
}

TEST(CRegionTest, SetRegionName) {
    CRegion region;
    region.SetRegionName("BaseRegion");
    EXPECT_STREQ(region.GetRegionName(), "BaseRegion");
}

TEST(CRegionTest, SetBounds) {
    CRegion region;
    region.SetBounds(0.0f, 0.0f, 100.0f, 100.0f);
    EXPECT_FLOAT_EQ(region.GetMinX(), 0.0f);
    EXPECT_FLOAT_EQ(region.GetMinY(), 0.0f);
    EXPECT_FLOAT_EQ(region.GetMaxX(), 100.0f);
    EXPECT_FLOAT_EQ(region.GetMaxY(), 100.0f);
}

TEST(CRegionTest, ContainsPoint) {
    CRegion region;
    region.SetBounds(10.0f, 10.0f, 50.0f, 50.0f);
    EXPECT_TRUE(region.ContainsPoint(25.0f, 25.0f));
    EXPECT_FALSE(region.ContainsPoint(5.0f, 5.0f));
    EXPECT_FALSE(region.ContainsPoint(60.0f, 60.0f));
}

TEST(CRegionTest, SetEnabled) {
    CRegion region;
    region.SetEnabled(false);
    EXPECT_FALSE(region.IsEnabled());
}

TEST(CRegionTest, SetVisible) {
    CRegion region;
    region.SetVisible(false);
    EXPECT_FALSE(region.IsVisible());
}
