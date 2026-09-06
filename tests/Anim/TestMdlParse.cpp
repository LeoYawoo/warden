#include <gtest/gtest.h>
#include "Anim/CMdlModel.h"
#include "Anim/MdlBinReader.h"
#include "Anim/MdlRender.h"
#include "Base/Status.h"
#include <fstream>
#include <vector>

// ============================================================================
// 测试用 MDX 文件路径
// ============================================================================

static const char* TEST_MDX_FOOTMAN = "data/mpq/war3.mpq.unpack/Units/Human/Footman/Footman.mdx";
static const char* TEST_MDX简单特效 = "data/mpq/war3.mpq.unpack/Abilities/Spells/Human/Heal/HealTarget.mdx";

// ============================================================================
// MDL 文件解析测试
// ============================================================================

class MdlParseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 检查测试文件是否存在
        std::ifstream footmanFile(TEST_MDX_FOOTMAN, std::ios::binary);
        footmanExists = footmanFile.good();
    }

    bool footmanExists = false;
};

// 测试文件加载
TEST_F(MdlParseTest, LoadFootmanModel) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found: " << TEST_MDX_FOOTMAN;
    }

    CMdlModel model;
    Status status;

    bool result = model.Load(TEST_MDX_FOOTMAN, status);

    EXPECT_TRUE(result) << "Failed to load model: " << status.GetMessage();
    EXPECT_TRUE(model.IsLoaded());
}

// 测试模型信息
TEST_F(MdlParseTest, ModelInfo) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    // 检查模型名称
    const char* name = model.GetName();
    EXPECT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);

    // 检查骨骼数量
    uint32_t boneCount = model.GetBoneCount();
    EXPECT_GT(boneCount, 0u);

    // 检查几何体数量
    uint32_t geosetCount = model.GetGeosetCount();
    EXPECT_GT(geosetCount, 0u);

    // 检查动画序列数量
    uint32_t seqCount = model.GetSequenceCount();
    EXPECT_GT(seqCount, 0u);
}

// 测试动画控制
TEST_F(MdlParseTest, AnimationControl) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    // 测试设置动画
    model.SetAnimation(0);
    EXPECT_EQ(model.GetAnimation(), 0u);

    // 测试获取动画时长
    uint32_t duration = model.GetAnimationDuration();
    EXPECT_GT(duration, 0u);

    // 测试更新动画
    model.SetLoop(true);
    model.Update(0.016f);  // 16ms
    EXPECT_EQ(model.GetTime(), 16u);

    // 测试循环
    model.SetTime(duration - 1);
    model.Update(0.016f);
    EXPECT_LT(model.GetTime(), duration);
}

// 测试骨骼矩阵
TEST_F(MdlParseTest, BoneMatrices) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    // 测试获取骨骼矩阵
    uint32_t boneCount = model.GetBoneCount();
    ASSERT_GT(boneCount, 0u);

    C44Matrix boneMatrix = model.GetBoneMatrix(0);
    // 矩阵应该是有效的 (不全为0)
    // 这里只检查不崩溃
}

// 测试包围盒
TEST_F(MdlParseTest, BoundingBox) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    CAaBox bounds = model.GetBoundingBox();
    // 包围盒应该是有效的
    // b (bottom) 应该小于等于 t (top)
    EXPECT_LE(bounds.b.x, bounds.t.x);
    EXPECT_LE(bounds.b.y, bounds.t.y);
    EXPECT_LE(bounds.b.z, bounds.t.z);
}

// ============================================================================
// MdlRender 测试
// ============================================================================

class MdlRenderTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ifstream footmanFile(TEST_MDX_FOOTMAN, std::ios::binary);
        footmanExists = footmanFile.good();
    }

    bool footmanExists = false;
};

// 测试渲染器初始化
TEST_F(MdlRenderTest, Initialize) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    MdlRender renderer;
    bool result = renderer.Initialize(model);

    EXPECT_TRUE(result);
    EXPECT_TRUE(renderer.IsInitialized());
}

// 测试渲染数据
TEST_F(MdlRenderTest, RenderData) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    MdlRender renderer;
    ASSERT_TRUE(renderer.Initialize(model));

    // 检查顶点数据
    const auto& vertices = renderer.GetVertices();
    EXPECT_GT(vertices.size(), 0u);

    // 检查索引数据
    const auto& indices = renderer.GetIndices();
    EXPECT_GT(indices.size(), 0u);

    // 检查批次数据
    const auto& batches = renderer.GetBatches();
    EXPECT_GT(batches.size(), 0u);

    // 检查骨骼矩阵
    const auto& boneMatrices = renderer.GetBoneMatrices();
    EXPECT_EQ(boneMatrices.size(), model.GetBoneCount());
}

// 测试渲染更新
TEST_F(MdlRenderTest, Update) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    MdlRender renderer;
    ASSERT_TRUE(renderer.Initialize(model));

    // 更新动画
    model.SetAnimation(0);
    model.Update(0.5f);

    // 更新渲染器
    renderer.Update(model);

    // 检查骨骼矩阵已更新
    const auto& boneMatrices = renderer.GetBoneMatrices();
    EXPECT_EQ(boneMatrices.size(), model.GetBoneCount());
}

// ============================================================================
// 错误处理测试
// ============================================================================

TEST(ErrorHandlingTest, InvalidFile) {
    CMdlModel model;
    Status status;

    bool result = model.Load("nonexistent.mdx", status);

    EXPECT_FALSE(result);
    EXPECT_FALSE(model.IsLoaded());
}

TEST(ErrorHandlingTest, InvalidSignature) {
    // 创建一个无效的 MDX 文件缓冲区
    uint8_t invalidData[] = { 'I', 'N', 'V', 'A', 'L', 'I', 'D', '\0' };

    CMdlModel model;
    Status status;

    bool result = model.LoadFromBuffer(invalidData, sizeof(invalidData), status);

    EXPECT_FALSE(result);
}

// ============================================================================
// 性能测试
// ============================================================================

class MdlPerformanceTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ifstream footmanFile(TEST_MDX_FOOTMAN, std::ios::binary);
        footmanExists = footmanFile.good();
    }

    bool footmanExists = false;
};

TEST_F(MdlPerformanceTest, LoadTime) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; i++) {
        CMdlModel model;
        Status status;
        model.Load(TEST_MDX_FOOTMAN, status);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 10 次加载应该在 1 秒内完成
    EXPECT_LT(duration.count(), 1000) << "Loading took too long: " << duration.count() << "ms";
}

TEST_F(MdlPerformanceTest, AnimationUpdate) {
    if (!footmanExists) {
        GTEST_SKIP() << "Test file not found";
    }

    CMdlModel model;
    Status status;
    ASSERT_TRUE(model.Load(TEST_MDX_FOOTMAN, status));

    model.SetAnimation(0);
    model.SetLoop(true);

    auto start = std::chrono::high_resolution_clock::now();

    // 更新 1000 帧
    for (int i = 0; i < 1000; i++) {
        model.Update(0.016f);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // 1000 帧更新应该在 10ms 内完成
    EXPECT_LT(duration.count(), 10000) << "Animation update took too long: " << duration.count() << "us";
}
