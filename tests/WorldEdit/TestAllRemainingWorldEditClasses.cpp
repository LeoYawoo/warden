#include <gtest/gtest.h>
#include "WorldEdit/CTerrainBlight.h"
#include "WorldEdit/CTerrainBounds.h"
#include "WorldEdit/CTerrainCliff.h"
#include "WorldEdit/CTerrainCliffDoodads.h"
#include "WorldEdit/CTerrainHeight.h"
#include "WorldEdit/CTerrainRamp.h"
#include "WorldEdit/CTerrainTextures.h"
#include "WorldEdit/CTerrainUberSplats.h"
#include "WorldEdit/CTerrainVertex.h"
#include "WorldEdit/CTerrainWater.h"
#include "WorldEdit/CWorldObjectsClippable.h"
#include "WorldEdit/MapInfoFile.h"
#include "WorldEdit/TestGameFile.h"
#include "WorldEdit/WEPreferences.h"
#include "WorldEdit/WEUtilities.h"

// MapInfoFile tests are in TestMoreWorldEditClasses.cpp
// TestGameFile tests are in TestMoreWorldEditClasses.cpp

// Test WEPreferences
TEST(WEPreferencesTest, DefaultConstructor) { WEPreferences p; }
TEST(WEPreferencesTest, SetGetIntPreference) { WEPreferences p; p.SetIntPreference("key", 42); EXPECT_EQ(p.GetIntPreference("key"), 42); }
TEST(WEPreferencesTest, SetGetFloatPreference) { WEPreferences p; p.SetFloatPreference("key", 3.14f); EXPECT_FLOAT_EQ(p.GetFloatPreference("key"), 3.14f); }
TEST(WEPreferencesTest, SetGetStringPreference) { WEPreferences p; p.SetStringPreference("key", "value"); EXPECT_STREQ(p.GetStringPreference("key"), "value"); }
TEST(WEPreferencesTest, SetGetBoolPreference) { WEPreferences p; p.SetBoolPreference("key", true); EXPECT_TRUE(p.GetBoolPreference("key")); }

// Test WEUtilities
TEST(WEUtilitiesTest, IsValidTile) { EXPECT_TRUE(WEUtilities::IsValidTile(5, 5, 10, 10)); EXPECT_FALSE(WEUtilities::IsValidTile(15, 5, 10, 10)); }
TEST(WEUtilitiesTest, GetTileIndex) { EXPECT_EQ(WEUtilities::GetTileIndex(3, 4, 10), 43); }
TEST(WEUtilitiesTest, WorldToTile) { int32_t tx, ty; WEUtilities::WorldToTile(256.0f, 384.0f, 128, tx, ty); EXPECT_EQ(tx, 2); EXPECT_EQ(ty, 3); }
TEST(WEUtilitiesTest, TileToWorld) { float wx, wy; WEUtilities::TileToWorld(2, 3, 128, wx, wy); EXPECT_FLOAT_EQ(wx, 256.0f); EXPECT_FLOAT_EQ(wy, 384.0f); }
TEST(WEUtilitiesTest, IsValidFileName) { EXPECT_TRUE(WEUtilities::IsValidFileName("test.w3m")); EXPECT_FALSE(WEUtilities::IsValidFileName("test<w3m")); EXPECT_FALSE(WEUtilities::IsValidFileName("")); }
TEST(WEUtilitiesTest, IsValidMapName) { EXPECT_TRUE(WEUtilities::IsValidMapName("TestMap")); EXPECT_FALSE(WEUtilities::IsValidMapName("")); }
