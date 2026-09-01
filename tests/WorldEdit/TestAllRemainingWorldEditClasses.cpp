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
#include "WorldEdit/TestGameFile.h"
#include "WorldEdit/WEPreferences.h"
#include "WorldEdit/WEUtilities.h"
#include "WorldEdit/CTerrain.h"

// Test CTerrainBlight
TEST(CTerrainBlightTest, DefaultConstructor) { CTerrainBlight b; EXPECT_FALSE(b.IsEnabled()); }
TEST(CTerrainBlightTest, SetEnabled) { CTerrainBlight b; b.SetEnabled(true); EXPECT_TRUE(b.IsEnabled()); }

// Test CTerrainBounds
TEST(CTerrainBoundsTest, DefaultConstructor) { CTerrainBounds b; EXPECT_FLOAT_EQ(b.GetMinX(), 0.0f); }
TEST(CTerrainBoundsTest, CalculateBounds) {
    CTerrain t; t.Initialize(10, 10, 128);
    CTerrainBounds b; b.CalculateBounds(&t);
    EXPECT_FLOAT_EQ(b.GetMaxX(), 1280.0f);
    EXPECT_FLOAT_EQ(b.GetMaxY(), 1280.0f);
}
TEST(CTerrainBoundsTest, IsInBounds) {
    CTerrain t; t.Initialize(1, 1, 100);
    CTerrainBounds b; b.CalculateBounds(&t);
    EXPECT_TRUE(b.IsInBounds(50.0f, 50.0f));
}

// Test CTerrainCliff
TEST(CTerrainCliffTest, DefaultConstructor) { CTerrainCliff c; EXPECT_EQ(c.GetCliffId(), 0); }
TEST(CTerrainCliffTest, SetCliffId) { CTerrainCliff c; c.SetCliffId(5); EXPECT_EQ(c.GetCliffId(), 5); }
TEST(CTerrainCliffTest, SetCliffLevel) { CTerrainCliff c; c.SetCliffLevel(3); EXPECT_EQ(c.GetCliffLevel(), 3); }
TEST(CTerrainCliffTest, SetActive) { CTerrainCliff c; c.SetActive(true); EXPECT_TRUE(c.IsActive()); }

// Test CTerrainCliffDoodads
TEST(CTerrainCliffDoodadsTest, DefaultConstructor) { CTerrainCliffDoodads d; EXPECT_EQ(d.GetDoodadId(), 0); }
TEST(CTerrainCliffDoodadsTest, SetDoodadId) { CTerrainCliffDoodads d; d.SetDoodadId(10); EXPECT_EQ(d.GetDoodadId(), 10); }
TEST(CTerrainCliffDoodadsTest, SetDoodadType) { CTerrainCliffDoodads d; d.SetDoodadType(2); EXPECT_EQ(d.GetDoodadType(), 2); }
TEST(CTerrainCliffDoodadsTest, SetActive) { CTerrainCliffDoodads d; d.SetActive(true); EXPECT_TRUE(d.IsActive()); }

// Test CTerrainHeight
TEST(CTerrainHeightTest, DefaultConstructor) { CTerrainHeight h; EXPECT_EQ(h.GetTerrain(), nullptr); }
TEST(CTerrainHeightTest, SetGetHeight) {
    CTerrain t; t.Initialize(10, 10, 128);
    CTerrainHeight h; h.SetTerrain(&t);
    h.SetHeight(5, 5, 100.0f);
    EXPECT_FLOAT_EQ(h.GetHeight(5, 5), 100.0f);
}

// Test CTerrainRamp
TEST(CTerrainRampTest, DefaultConstructor) { CTerrainRamp r; EXPECT_EQ(r.GetRampId(), 0); }
TEST(CTerrainRampTest, SetRampId) { CTerrainRamp r; r.SetRampId(7); EXPECT_EQ(r.GetRampId(), 7); }
TEST(CTerrainRampTest, SetSlope) { CTerrainRamp r; r.SetSlope(0.5f); EXPECT_FLOAT_EQ(r.GetSlope(), 0.5f); }

// Test CTerrainTextures
TEST(CTerrainTexturesTest, DefaultConstructor) { CTerrainTextures t; EXPECT_EQ(t.GetTextureId(), 0); }
TEST(CTerrainTexturesTest, SetTextureId) { CTerrainTextures t; t.SetTextureId(3); EXPECT_EQ(t.GetTextureId(), 3); }
TEST(CTerrainTexturesTest, SetTextureName) { CTerrainTextures t; t.SetTextureName("grass"); EXPECT_STREQ(t.GetTextureName(), "grass"); }

// Test CTerrainUberSplats
TEST(CTerrainUberSplatsTest, DefaultConstructor) { CTerrainUberSplats u; EXPECT_EQ(u.GetSplatId(), 0); }
TEST(CTerrainUberSplatsTest, SetSplatId) { CTerrainUberSplats u; u.SetSplatId(5); EXPECT_EQ(u.GetSplatId(), 5); }
TEST(CTerrainUberSplatsTest, SetScale) { CTerrainUberSplats u; u.SetScale(2.0f); EXPECT_FLOAT_EQ(u.GetScale(), 2.0f); }

// Test CTerrainVertex
TEST(CTerrainVertexTest, DefaultConstructor) { CTerrainVertex v; EXPECT_FLOAT_EQ(v.GetX(), 0.0f); }
TEST(CTerrainVertexTest, SetPosition) { CTerrainVertex v; v.SetPosition(1, 2, 3); EXPECT_FLOAT_EQ(v.GetX(), 1.0f); EXPECT_FLOAT_EQ(v.GetY(), 2.0f); EXPECT_FLOAT_EQ(v.GetZ(), 3.0f); }
TEST(CTerrainVertexTest, SetNormal) { CTerrainVertex v; v.SetNormal(0, 1, 0); EXPECT_FLOAT_EQ(v.GetNormalY(), 1.0f); }

// Test CTerrainWater
TEST(CTerrainWaterTest, DefaultConstructor) { CTerrainWater w; EXPECT_FALSE(w.IsActive()); }
TEST(CTerrainWaterTest, SetWaterLevel) { CTerrainWater w; w.SetWaterLevel(10.0f); EXPECT_FLOAT_EQ(w.GetWaterLevel(), 10.0f); }
TEST(CTerrainWaterTest, SetActive) { CTerrainWater w; w.SetActive(true); EXPECT_TRUE(w.IsActive()); }

// Test CWorldObjectsClippable
TEST(CWorldObjectsClippableTest, DefaultConstructor) { CWorldObjectsClippable c; EXPECT_FALSE(c.IsClipped()); }
TEST(CWorldObjectsClippableTest, SetClipped) { CWorldObjectsClippable c; c.SetClipped(true); EXPECT_TRUE(c.IsClipped()); }
TEST(CWorldObjectsClippableTest, SetClipRadius) { CWorldObjectsClippable c; c.SetClipRadius(50.0f); EXPECT_FLOAT_EQ(c.GetClipRadius(), 50.0f); }

// Test TestGameFile
TEST(TestGameFileTest, DefaultConstructor) { TestGameFile f; EXPECT_FALSE(f.IsLoaded()); EXPECT_FALSE(f.IsValid()); }
TEST(TestGameFileTest, Load) { TestGameFile f; EXPECT_TRUE(f.Load("test.w3g")); EXPECT_TRUE(f.IsLoaded()); EXPECT_TRUE(f.IsValid()); }
TEST(TestGameFileTest, Close) { TestGameFile f; f.Load("test.w3g"); f.Close(); EXPECT_FALSE(f.IsLoaded()); }

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
