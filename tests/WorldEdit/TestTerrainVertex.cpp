#include <gtest/gtest.h>
#include "Tempest/C3Vector.h"

// Test TerrainVertex-like structure without CTerrain dependency
struct TestTerrainVertex {
    uint32_t flags;
    uint32_t cellIndex;
    uint8_t textureLayer;
    uint8_t cliffLevel;
    uint8_t flags2;
    uint8_t waterEdge;
    Tempest::C3Vector normal;

    TestTerrainVertex() : flags(0), cellIndex(0), textureLayer(0), cliffLevel(0),
                          flags2(0), waterEdge(0), normal(0.0f, 0.0f, 1.0f) {}

    float GetHeight() const {
        return static_cast<float>((flags >> 16) & 0xFFFF) / 256.0f;
    }

    void SetHeight(float height) {
        uint16_t h = static_cast<uint16_t>(height * 256.0f);
        flags = (flags & 0x0000FFFF) | (static_cast<uint32_t>(h) << 16);
    }

    bool IsWater() const {
        return (flags & 0x1) != 0;
    }

    void SetWater(bool water) {
        if (water) {
            flags |= 0x1;
        } else {
            flags &= ~0x1;
        }
    }

    uint32_t GetCellIndex() const {
        return cellIndex & 0x3FFFF;
    }

    void SetCellIndex(uint32_t index) {
        cellIndex = (cellIndex & ~0x3FFFF) | (index & 0x3FFFF);
    }

    void NormalizeNormal() {
        float len = normal.Mag();
        if (len > 0.0001f) {
            float invLen = 1.0f / len;
            normal.x *= invLen;
            normal.y *= invLen;
            normal.z *= invLen;
        }
    }

    bool operator==(const TestTerrainVertex &other) const {
        return flags == other.flags && cellIndex == other.cellIndex &&
               textureLayer == other.textureLayer && cliffLevel == other.cliffLevel &&
               normal == other.normal;
    }

    bool operator!=(const TestTerrainVertex &other) const {
        return !(*this == other);
    }
};

TEST(TerrainVertexTest, DefaultConstructor) {
    TestTerrainVertex v;
    EXPECT_EQ(v.flags, 0u);
    EXPECT_EQ(v.cellIndex, 0u);
    EXPECT_EQ(v.textureLayer, 0);
    EXPECT_EQ(v.cliffLevel, 0);
    EXPECT_FLOAT_EQ(v.normal.x, 0.0f);
    EXPECT_FLOAT_EQ(v.normal.y, 0.0f);
    EXPECT_FLOAT_EQ(v.normal.z, 1.0f);
}

TEST(TerrainVertexTest, GetHeight) {
    TestTerrainVertex v;
    v.flags = 0x01000000;  // Height = 256 in upper 16 bits
    EXPECT_NEAR(v.GetHeight(), 1.0f, 0.01f);
}

TEST(TerrainVertexTest, SetHeight) {
    TestTerrainVertex v;
    v.SetHeight(2.0f);
    EXPECT_NEAR(v.GetHeight(), 2.0f, 0.01f);
}

TEST(TerrainVertexTest, HeightRoundTrip) {
    TestTerrainVertex v;
    v.SetHeight(3.5f);
    float height = v.GetHeight();
    EXPECT_NEAR(height, 3.5f, 0.01f);
}

TEST(TerrainVertexTest, IsWater) {
    TestTerrainVertex v;
    EXPECT_FALSE(v.IsWater());

    v.SetWater(true);
    EXPECT_TRUE(v.IsWater());

    v.SetWater(false);
    EXPECT_FALSE(v.IsWater());
}

TEST(TerrainVertexTest, GetCellIndex) {
    TestTerrainVertex v;
    v.cellIndex = 0x12345;
    EXPECT_EQ(v.GetCellIndex(), 0x12345u);
}

TEST(TerrainVertexTest, SetCellIndex) {
    TestTerrainVertex v;
    v.SetCellIndex(0x12345);
    EXPECT_EQ(v.GetCellIndex(), 0x12345u);
}

TEST(TerrainVertexTest, NormalizeNormal) {
    TestTerrainVertex v;
    v.normal = Tempest::C3Vector(3.0f, 4.0f, 0.0f);
    v.NormalizeNormal();

    float len = v.normal.Mag();
    EXPECT_NEAR(len, 1.0f, 0.001f);
}

TEST(TerrainVertexTest, Equality) {
    TestTerrainVertex a;
    TestTerrainVertex b;
    EXPECT_TRUE(a == b);

    b.textureLayer = 1;
    EXPECT_FALSE(a == b);
}

TEST(TerrainVertexTest, Inequality) {
    TestTerrainVertex a;
    a.textureLayer = 0;
    TestTerrainVertex b;
    b.textureLayer = 1;
    EXPECT_TRUE(a != b);
}

TEST(TerrainVertexTest, Size) {
    EXPECT_EQ(sizeof(TestTerrainVertex), 24u);
}
