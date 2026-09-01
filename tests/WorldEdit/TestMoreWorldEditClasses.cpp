#include <gtest/gtest.h>
#include "WorldEdit/CWeatherEmitter.h"
#include "WorldEdit/CTerrainDeformation.h"
#include "WorldEdit/MapInfoFile.h"
#include "WorldEdit/CTerrain.h"

// Test CWeatherEmitter
TEST(CWeatherEmitterTest, DefaultConstructor) {
    CWeatherEmitter emitter;
    EXPECT_EQ(emitter.GetEmitterId(), 0);
    EXPECT_FALSE(emitter.IsEnabled());
    EXPECT_FALSE(emitter.IsPlaying());
}

TEST(CWeatherEmitterTest, SetEmitterId) {
    CWeatherEmitter emitter;
    emitter.SetEmitterId(42);
    EXPECT_EQ(emitter.GetEmitterId(), 42);
}

TEST(CWeatherEmitterTest, SetEmitterName) {
    CWeatherEmitter emitter;
    emitter.SetEmitterName("RainEmitter");
    EXPECT_STREQ(emitter.GetEmitterName(), "RainEmitter");
}

TEST(CWeatherEmitterTest, SetEnabled) {
    CWeatherEmitter emitter;
    emitter.SetEnabled(true);
    EXPECT_TRUE(emitter.IsEnabled());
}

TEST(CWeatherEmitterTest, SetPlaying) {
    CWeatherEmitter emitter;
    emitter.SetPlaying(true);
    EXPECT_TRUE(emitter.IsPlaying());
}

TEST(CWeatherEmitterTest, SetEmissionRate) {
    CWeatherEmitter emitter;
    emitter.SetEmissionRate(10.5f);
    EXPECT_FLOAT_EQ(emitter.GetEmissionRate(), 10.5f);
}

TEST(CWeatherEmitterTest, SetLifetime) {
    CWeatherEmitter emitter;
    emitter.SetLifetime(5.0f);
    EXPECT_FLOAT_EQ(emitter.GetLifetime(), 5.0f);
}

TEST(CWeatherEmitterTest, SetSpeed) {
    CWeatherEmitter emitter;
    emitter.SetSpeed(2.0f);
    EXPECT_FLOAT_EQ(emitter.GetSpeed(), 2.0f);
}

TEST(CWeatherEmitterTest, SetSpread) {
    CWeatherEmitter emitter;
    emitter.SetSpread(45.0f);
    EXPECT_FLOAT_EQ(emitter.GetSpread(), 45.0f);
}

TEST(CWeatherEmitterTest, SetPosition) {
    CWeatherEmitter emitter;
    emitter.SetPosition(100.0f, 200.0f);
    EXPECT_FLOAT_EQ(emitter.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(emitter.GetY(), 200.0f);
}

// Test CTerrainDeformation
TEST(CTerrainDeformationTest, DefaultConstructor) {
    CTerrainDeformation deform;
    EXPECT_EQ(deform.GetDeformationId(), 0);
    EXPECT_FALSE(deform.IsActive());
    EXPECT_EQ(deform.GetFunctionCount(), 0u);
}

TEST(CTerrainDeformationTest, SetDeformationId) {
    CTerrainDeformation deform;
    deform.SetDeformationId(10);
    EXPECT_EQ(deform.GetDeformationId(), 10);
}

TEST(CTerrainDeformationTest, SetActive) {
    CTerrainDeformation deform;
    deform.SetActive(true);
    EXPECT_TRUE(deform.IsActive());
}

TEST(CTerrainDeformationTest, AddFunction) {
    CTerrainDeformation deform;
    float params[] = {1.0f, 2.0f, 3.0f};
    deform.AddFunction(1, 3, params);
    EXPECT_EQ(deform.GetFunctionCount(), 1u);
}

TEST(CTerrainDeformationTest, RemoveFunction) {
    CTerrainDeformation deform;
    float params[] = {1.0f};
    deform.AddFunction(1, 1, params);
    deform.AddFunction(2, 1, params);
    EXPECT_EQ(deform.GetFunctionCount(), 2u);

    deform.RemoveFunction(1);
    EXPECT_EQ(deform.GetFunctionCount(), 1u);
}

TEST(CTerrainDeformationTest, Apply) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);

    CTerrainDeformation deform;
    deform.SetActive(true);

    float params[] = {1.0f};
    deform.AddFunction(1, 1, params);

    // Apply at center (64, 64) which is tile (0, 0)
    deform.Apply(&terrain, 64.0f, 64.0f, 200.0f, 10.0f);
    // Verify deformation was applied at tile (0, 0)
    EXPECT_NE(terrain.GetHeight(0, 0), 0.0f);
}

TEST(CTerrainDeformationTest, ApplyInactive) {
    CTerrain terrain;
    terrain.Initialize(10, 10, 128);

    CTerrainDeformation deform;
    deform.SetActive(false);

    deform.Apply(&terrain, 64.0f, 64.0f, 200.0f, 10.0f);
    // Verify no deformation when inactive
    EXPECT_FLOAT_EQ(terrain.GetHeight(5, 5), 0.0f);
}

// Test MapInfoFile
TEST(MapInfoFileTest, DefaultConstructor) {
    MapInfoFile info;
    EXPECT_FALSE(info.IsValid());
    EXPECT_EQ(info.GetMapVersion(), 0);
    EXPECT_EQ(info.GetMapSize(), 0);
}

TEST(MapInfoFileTest, SetFileName) {
    MapInfoFile info;
    info.SetFileName("test.w3m");
    EXPECT_STREQ(info.GetFileName(), "test.w3m");
}

TEST(MapInfoFileTest, SetMapName) {
    MapInfoFile info;
    info.SetMapName("Test Map");
    EXPECT_STREQ(info.GetMapName(), "Test Map");
}

TEST(MapInfoFileTest, SetMapDescription) {
    MapInfoFile info;
    info.SetMapDescription("A test map");
    EXPECT_STREQ(info.GetMapDescription(), "A test map");
}

TEST(MapInfoFileTest, SetAuthor) {
    MapInfoFile info;
    info.SetAuthor("Test Author");
    EXPECT_STREQ(info.GetAuthor(), "Test Author");
}

TEST(MapInfoFileTest, SetMapVersion) {
    MapInfoFile info;
    info.SetMapVersion(3);
    EXPECT_EQ(info.GetMapVersion(), 3);
}

TEST(MapInfoFileTest, SetMapSize) {
    MapInfoFile info;
    info.SetMapSize(128);
    EXPECT_EQ(info.GetMapSize(), 128);
}

TEST(MapInfoFileTest, SetMapFlags) {
    MapInfoFile info;
    info.SetMapFlags(0x01);
    EXPECT_EQ(info.GetMapFlags(), 0x01);
}

TEST(MapInfoFileTest, Load) {
    MapInfoFile info;
    EXPECT_TRUE(info.Load("test.w3m"));
    EXPECT_TRUE(info.IsValid());
}

TEST(MapInfoFileTest, Save) {
    MapInfoFile info;
    info.SetFileName("test.w3m");
    EXPECT_TRUE(info.Save("test.w3m"));
}
