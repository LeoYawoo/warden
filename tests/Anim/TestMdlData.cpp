#include <gtest/gtest.h>
#include "Anim/MdlData.h"
#include "Anim/MdlKeyTrack.h"
#include "Anim/MdlBinReader.h"
#include "Anim/CMdlModel.h"

// ============================================================================
// MDLArray 测试
// ============================================================================

TEST(MdlArrayTest, DefaultConstructor) {
    MDLArray<int> arr;
    EXPECT_EQ(arr.count, 0u);
    EXPECT_EQ(arr.offset, 0u);
}

TEST(MdlArrayTest, Count) {
    MDLArray<int> arr;
    arr.count = 10;
    EXPECT_EQ(arr.Count(), 10u);
}

// ============================================================================
// 关键帧结构体测试
// ============================================================================

TEST(MdlKeyFrameTest, MDLCOORD3FKEYFRAME) {
    MDLCOORD3FKEYFRAME key(1.0f, 2.0f, 3.0f, 100);
    EXPECT_FLOAT_EQ(key.x, 1.0f);
    EXPECT_FLOAT_EQ(key.y, 2.0f);
    EXPECT_FLOAT_EQ(key.z, 3.0f);
    EXPECT_EQ(key.time, 100u);
}

TEST(MdlKeyFrameTest, MDLTRANSKEYFRAME) {
    MDLTRANSKEYFRAME key(1.0f, 2.0f, 3.0f, 100);
    EXPECT_FLOAT_EQ(key.x, 1.0f);
    EXPECT_EQ(key.time, 100u);
}

TEST(MdlKeyFrameTest, MDLROTKEYFRAME) {
    MDLROTKEYFRAME key(0.0f, 0.0f, 0.0f, 1.0f, 100);
    EXPECT_FLOAT_EQ(key.w, 1.0f);
    EXPECT_EQ(key.time, 100u);
}

TEST(MdlKeyFrameTest, MDLSCALEKEYFRAME) {
    MDLSCALEKEYFRAME key(2.0f, 2.0f, 2.0f, 100);
    EXPECT_FLOAT_EQ(key.x, 2.0f);
}

TEST(MdlKeyFrameTest, MDLALPHAKEYFRAME) {
    MDLALPHAKEYFRAME key(0.5f, 100);
    EXPECT_FLOAT_EQ(key.alpha, 0.5f);
}

TEST(MdlKeyFrameTest, MDLCOLORKEYFRAME) {
    MDLCOLORKEYFRAME key(255, 128, 64, 100);
    EXPECT_EQ(key.r, 255);
    EXPECT_EQ(key.g, 128);
    EXPECT_EQ(key.b, 64);
}

// ============================================================================
// Section 结构体测试
// ============================================================================

TEST(MdlSectionTest, MDLHEADERSECTION) {
    MDLHEADERSECTION header;
    EXPECT_EQ(header.hasAnimation, 0);
    EXPECT_STREQ(header.name, "");
}

TEST(MdlSectionTest, MDLSEQUENCESSECTION) {
    MDLSEQUENCESSECTION seq;
    EXPECT_EQ(seq.moveSpeed, 0.0f);
    EXPECT_EQ(seq.flags, 0u);
    EXPECT_EQ(seq.nextAnimation, -1);
}

TEST(MdlSectionTest, MDLMATERIALSECTION) {
    MDLMATERIALSECTION mat;
    EXPECT_EQ(mat.flags, 0u);
    EXPECT_EQ(mat.blendMode, 0);
}

TEST(MdlSectionTest, MDLBONESECTION) {
    MDLBONESECTION bone;
    EXPECT_EQ(bone.nodeId, 0u);
    EXPECT_EQ(bone.parentBone, -1);
}

// ============================================================================
// MDLKEYTRACK 测试
// ============================================================================

TEST(MdlKeyTrackTest, DefaultConstructor) {
    MDLKEYTRACK<MDLTRANSKEYFRAME> track;
    EXPECT_EQ(track.interpolationType, MDL_TRACKTYPE_NONE);
}

TEST(MdlKeyTrackTest, LinearInterpolation) {
    MDLKEYTRACK<MDLTRANSKEYFRAME> track;
    track.interpolationType = MDL_TRACKTYPE_LINEAR;

    // 分配关键帧数据
    MDLTRANSKEYFRAME* keys = new MDLTRANSKEYFRAME[2];
    keys[0] = MDLTRANSKEYFRAME(0.0f, 0.0f, 0.0f, 0);
    keys[1] = MDLTRANSKEYFRAME(10.0f, 10.0f, 10.0f, 100);

    track.keys.count = 2;
    track.keys.offset = reinterpret_cast<uintptr_t>(keys);

    // 测试插值
    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, 50, keyIndex, ratio);

    EXPECT_EQ(keyIndex, 1u);
    EXPECT_NEAR(ratio, 0.5f, 0.01f);

    delete[] keys;
}

// ============================================================================
// MdlInterp 测试
// ============================================================================

TEST(MdlInterpTest, DefaultConstructor) {
    MdlInterp interp;
    // 默认构造不应该崩溃
}

// ============================================================================
// CMdlModel 测试
// ============================================================================

TEST(CMdlModelTest, DefaultConstructor) {
    CMdlModel model;
    EXPECT_FALSE(model.IsLoaded());
    EXPECT_EQ(model.GetBoneCount(), 0u);
    EXPECT_EQ(model.GetSequenceCount(), 0u);
}

TEST(CMdlModelTest, GetName) {
    CMdlModel model;
    EXPECT_STREQ(model.GetName(), "");
}

TEST(CMdlModelTest, AnimationControl) {
    CMdlModel model;
    // 未加载时设置动画不应该崩溃
    model.SetAnimation(0);
    model.SetTime(0);
    model.Update(0.016f);
}
