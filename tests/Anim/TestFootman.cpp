#include <gtest/gtest.h>
#include "Anim/CMdlModel.h"
#include "Anim/MdlBinReader.h"
#include "Anim/MdlRender.h"
#include "Anim/MdlInterp.h"
#include "Anim/MdlKeyTrack.h"
#include "Anim/MdlData.h"
#include "Base/Status.h"
#include "Model/ModelCreate.h"
#include <fstream>
#include <cmath>
#include <vector>

using namespace Tempest;

// ============================================================================
// C44Matrix 辅助访问函数 (C44Matrix 使用命名成员 a0..d3，无 operator[])
// ============================================================================

static float MatAt(const C44Matrix& m, int r, int c) {
    const float* rows[4] = { &m.a0, &m.b0, &m.c0, &m.d0 };
    return *(rows[r] + c);
}

// ============================================================================
// Footman.mdx 路径解析 (通过 __FILE__ 定位项目根目录)
// ============================================================================

static std::string GetFootmanPath() {
    std::string path = __FILE__;
    for (auto& c : path) { if (c == '\\') c = '/'; }
    size_t pos = path.find("tests/Anim/TestFootman.cpp");
    if (pos != std::string::npos) {
        path = path.substr(0, pos) + "data/mpq/war3.mpq.unpack/Units/Human/Footman/Footman.mdx";
    }
    return path;
}

// ============================================================================
// Footman.mdx 真实数据测试
// ============================================================================

class FootmanTest : public ::testing::Test {
protected:
    void SetUp() override {
        footmanPath = GetFootmanPath();
        std::ifstream f(footmanPath, std::ios::binary);
        fileExists = f.good();
        if (!fileExists) return;

        model = std::make_unique<CMdlModel>();
        Status status;
        loaded = model->Load(footmanPath.c_str(), status);
        if (!loaded) {
            errorMsg = status.GetMessage();
        }
    }

    std::string footmanPath;
    bool fileExists = false;
    bool loaded = false;
    std::string errorMsg;
    std::unique_ptr<CMdlModel> model;
};

// ============================================================================
// 1. 基本加载
// ============================================================================

TEST_F(FootmanTest, LoadSuccess) {
    if (!fileExists) GTEST_SKIP() << "Footman.mdx not found";
    EXPECT_TRUE(loaded) << "Load failed: " << errorMsg;
    EXPECT_TRUE(model->IsLoaded());
}

TEST_F(FootmanTest, ModelName) {
    if (!fileExists || !loaded) GTEST_SKIP();
    const char* name = model->GetName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "Footman");
}

// ============================================================================
// 2. 包围盒 (从 MODL chunk 解析)
// ============================================================================

TEST_F(FootmanTest, BoundingBoxValid) {
    if (!fileExists || !loaded) GTEST_SKIP();
    CAaBox box = model->GetBoundingBox();
    EXPECT_LE(box.b.x, box.t.x);
    EXPECT_LE(box.b.y, box.t.y);
    EXPECT_LE(box.b.z, box.t.z);
}

// ============================================================================
// 3. 原始数据验证 — MODL chunk 内容
// ============================================================================

TEST_F(FootmanTest, RawDataAccessible) {
    if (!fileExists || !loaded) GTEST_SKIP();
    const MDLDATA* data = model->GetData();
    ASSERT_NE(data, nullptr);
    EXPECT_STREQ(data->header.name, "Footman");
    // section 数量依赖于对应 chunk 的解析 (目前只解析了 MODL)
    EXPECT_EQ(data->bones.Count(), model->GetBoneCount());
    EXPECT_EQ(data->geosets.Count(), model->GetGeosetCount());
    EXPECT_EQ(data->sequences.Count(), model->GetSequenceCount());
}

// ============================================================================
// 4. 动画控制接口 (不依赖 chunk 数据)
// ============================================================================

TEST_F(FootmanTest, AnimationControlSafe) {
    if (!fileExists || !loaded) GTEST_SKIP();
    // 设置/获取动画不应崩溃 (即使没有序列数据)
    model->SetAnimation(0);
    model->SetTime(0);
    model->SetLoop(true);
    model->Update(0.016f);
    model->SetLoop(false);
    model->Update(0.016f);
}

TEST_F(FootmanTest, SetInvalidAnimation) {
    if (!fileExists || !loaded) GTEST_SKIP();
    model->SetAnimation(99999);
    // 无序列数据时 SetAnimation 不会改变当前索引
    // 有数据时索引不应超过范围
    if (model->GetSequenceCount() > 0) {
        EXPECT_LT(model->GetAnimation(), model->GetSequenceCount());
    }
}

// ============================================================================
// 5. 骨骼矩阵 (越界安全)
// ============================================================================

TEST_F(FootmanTest, OutOfRangeBoneReturnsIdentity) {
    if (!fileExists || !loaded) GTEST_SKIP();
    C44Matrix mat = model->GetBoneMatrix(99999);
    EXPECT_NEAR(MatAt(mat, 0, 0), 1.0f, 0.001f);
    EXPECT_NEAR(MatAt(mat, 1, 1), 1.0f, 0.001f);
    EXPECT_NEAR(MatAt(mat, 2, 2), 1.0f, 0.001f);
    EXPECT_NEAR(MatAt(mat, 3, 3), 1.0f, 0.001f);
}

TEST_F(FootmanTest, GeosetAlphaDefault) {
    if (!fileExists || !loaded) GTEST_SKIP();
    model->SetAnimation(0);
    model->SetTime(0);
    // 无 geoset 数据时应返回默认值 1.0
    float alpha = model->GetGeosetAlpha(0);
    EXPECT_FLOAT_EQ(alpha, 1.0f);
}

// ============================================================================
// 6. ModelCreate 工厂
// ============================================================================

TEST_F(FootmanTest, ModelCreateFactory) {
    if (!fileExists) GTEST_SKIP();
    void* created = ModelCreate::CreateModel(footmanPath.c_str());
    ASSERT_NE(created, nullptr) << "ModelCreate::CreateModel should succeed for .mdx";
    CMdlModel* mdl = static_cast<CMdlModel*>(created);
    EXPECT_TRUE(mdl->IsLoaded());
    EXPECT_STREQ(mdl->GetName(), "Footman");
    mdl->Release();
    delete mdl;
}

TEST_F(FootmanTest, ModelCreateIsMdlFile) {
    EXPECT_TRUE(ModelCreate::IsMdlFile("hero.mdx"));
    EXPECT_TRUE(ModelCreate::IsMdlFile("hero.MDX"));
    EXPECT_TRUE(ModelCreate::IsMdlFile("hero.mdl"));
    EXPECT_TRUE(ModelCreate::IsMdlFile("hero.MDL"));
    EXPECT_FALSE(ModelCreate::IsMdlFile("hero.m2"));
    EXPECT_FALSE(ModelCreate::IsMdlFile("hero.blp"));
    EXPECT_FALSE(ModelCreate::IsMdlFile(nullptr));
}

TEST_F(FootmanTest, ModelCreateGetExtension) {
    EXPECT_EQ(ModelCreate::GetExtension("hero.mdx"), ".mdx");
    EXPECT_EQ(ModelCreate::GetExtension("hero.MDX"), ".mdx");
    EXPECT_EQ(ModelCreate::GetExtension("path/to/hero.mdl"), ".mdl");
    EXPECT_EQ(ModelCreate::GetExtension("noext"), "");
    EXPECT_EQ(ModelCreate::GetExtension(nullptr), "");
}

TEST_F(FootmanTest, ModelCreateInvalidFile) {
    void* result = ModelCreate::CreateModel("nonexistent.mdx");
    EXPECT_EQ(result, nullptr);
}

TEST_F(FootmanTest, ModelCreateNullPath) {
    void* result = ModelCreate::CreateModel(nullptr);
    EXPECT_EQ(result, nullptr);
}

// ============================================================================
// 7. MdlBinReader 直接解析
// ============================================================================

TEST_F(FootmanTest, BinReaderDirectParse) {
    if (!fileExists) GTEST_SKIP();
    MdlBinReader reader;
    MDLDATA data;
    Status status;
    bool result = reader.ReadFile(footmanPath.c_str(), data, status);
    if (result) {
        EXPECT_STREQ(data.header.name, "Footman");
    }
}

// ============================================================================
// 8. LoadFromBuffer
// ============================================================================

TEST_F(FootmanTest, LoadFromBuffer) {
    if (!fileExists) GTEST_SKIP();
    std::ifstream file(footmanPath, std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(static_cast<size_t>(size));
    ASSERT_TRUE(file.read(reinterpret_cast<char*>(buffer.data()), size));

    CMdlModel bufferModel;
    Status status;
    bool result = bufferModel.LoadFromBuffer(buffer.data(), static_cast<uint32_t>(size), status);
    EXPECT_TRUE(result) << "LoadFromBuffer failed: " << status.GetMessage();
    EXPECT_TRUE(bufferModel.IsLoaded());
    EXPECT_STREQ(bufferModel.GetName(), "Footman");
}

// ============================================================================
// 9. 错误处理
// ============================================================================

TEST(ErrorHandling, InvalidFile) {
    CMdlModel model;
    Status status;
    bool result = model.Load("nonexistent.mdx", status);
    EXPECT_FALSE(result);
    EXPECT_FALSE(model.IsLoaded());
}

TEST(ErrorHandling, InvalidSignature) {
    uint8_t badData[] = { 'B', 'A', 'D', '!', 0, 0, 0, 0, 0, 0, 0, 0 };
    CMdlModel model;
    Status status;
    bool result = model.LoadFromBuffer(badData, sizeof(badData), status);
    EXPECT_FALSE(result);
}

TEST(ErrorHandling, EmptyBuffer) {
    uint8_t empty[] = {};
    CMdlModel model;
    Status status;
    bool result = model.LoadFromBuffer(empty, 0, status);
    EXPECT_FALSE(result);
}

// ============================================================================
// 10. 多次加载/释放
// ============================================================================

TEST_F(FootmanTest, LoadReleaseReload) {
    if (!fileExists) GTEST_SKIP();
    for (int i = 0; i < 3; ++i) {
        CMdlModel m;
        Status status;
        EXPECT_TRUE(m.Load(footmanPath.c_str(), status)) << "Iteration " << i;
        EXPECT_TRUE(m.IsLoaded());
        EXPECT_STREQ(m.GetName(), "Footman");
    }
}

TEST_F(FootmanTest, ReleaseResetState) {
    if (!fileExists) GTEST_SKIP();
    model->SetAnimation(0);
    model->Update(0.5f);
    model->Release();
    EXPECT_FALSE(model->IsLoaded());
    EXPECT_EQ(model->GetBoneCount(), 0u);
    EXPECT_EQ(model->GetSequenceCount(), 0u);
}

// ============================================================================
// 11. MdlInterp 初始化
// ============================================================================

TEST_F(FootmanTest, InterpSafe) {
    if (!fileExists || !loaded) GTEST_SKIP();
    MdlInterp interp;
    const MDLDATA* data = model->GetData();
    ASSERT_NE(data, nullptr);
    interp.Initialize(*data);
    interp.Update(0);
    // 获取骨骼矩阵和 geoset alpha 不应崩溃
    C44Matrix mat = interp.GetBoneMatrix(0);
    (void)mat;
    float alpha = interp.GetGeosetAlpha(0);
    (void)alpha;
}
