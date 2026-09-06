#pragma once

#include "MdlData.h"
#include "MdlKeyTrack.h"
#include "../Tempest/C3Vector.h"
#include "../Tempest/C44Matrix.h"
#include <cstdint>
#include <vector>

using namespace Tempest;

// ============================================================================
// MdlInterp - MDL 动画插值系统
// 基于 IDA 反编译的暴雪原始代码实现
// ============================================================================

class MdlInterp {
public:
    MdlInterp();
    ~MdlInterp();

    // 初始化动画状态
    void Initialize(const MDLDATA& data);

    // 更新动画时间
    void Update(uint32_t time);

    // 获取骨骼变换矩阵
    C44Matrix GetBoneMatrix(uint32_t boneIndex) const;

    // 获取几何体动画 alpha
    float GetGeosetAlpha(uint32_t geosetIndex) const;

    // 获取纹理动画变换
    C44Matrix GetTextureTransform(uint32_t texAnimIndex) const;

private:
    const MDLDATA* m_data;
    uint32_t m_currentTime;

    // 缓存的骨骼变换
    mutable std::vector<C44Matrix> m_boneMatrices;
    mutable bool m_boneMatricesDirty;

    // 缓存的几何体 alpha
    mutable std::vector<float> m_geosetAlphas;
    mutable bool m_geosetAlphasDirty;

    // 重新计算骨骼矩阵
    void RecalculateBoneMatrices() const;

    // 重新计算几何体 alpha
    void RecalculateGeosetAlphas() const;

    // 计算单个骨骼的本地变换
    C44Matrix CalculateBoneLocalTransform(const MDLBONESECTION& bone) const;
};

// ============================================================================
// 便捷函数
// ============================================================================

// 获取骨骼动画变换
inline C44Matrix MdlGetBoneTransform(const MDLDATA& data, uint32_t boneIndex, uint32_t time) {
    if (boneIndex >= data.bones.Count()) {
        return C44Matrix();  // 返回单位矩阵
    }

    const auto& bone = data.bones[boneIndex];

    // 获取动画值
    C3Vector translation = MdlGetTransValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLTRANSKEYFRAME>*>(&bone.translationTrack),
        time
    );

    MDLROTKEYFRAME rotation = MdlGetRotValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLROTKEYFRAME>*>(&bone.rotationTrack),
        time
    );

    C3Vector scale = MdlGetScaleValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLSCALEKEYFRAME>*>(&bone.scaleTrack),
        time
    );

    // 构建变换矩阵
    C44Matrix mat = C44Matrix::Identity();

    // 平移
    mat.Translate(translation);

    // 旋转 (四元数转矩阵)
    float x2 = rotation.x + rotation.x;
    float y2 = rotation.y + rotation.y;
    float z2 = rotation.z + rotation.z;
    float xx = rotation.x * x2;
    float xy = rotation.x * y2;
    float xz = rotation.x * z2;
    float yy = rotation.y * y2;
    float yz = rotation.y * z2;
    float zz = rotation.z * z2;
    float wx = rotation.w * x2;
    float wy = rotation.w * y2;
    float wz = rotation.w * z2;

    mat.a0 = 1.0f - (yy + zz);
    mat.a1 = xy + wz;
    mat.a2 = xz - wy;
    mat.b0 = xy - wz;
    mat.b1 = 1.0f - (xx + zz);
    mat.b2 = yz + wx;
    mat.c0 = xz + wy;
    mat.c1 = yz - wx;
    mat.c2 = 1.0f - (xx + yy);

    // 缩放
    mat.a0 *= scale.x;
    mat.b1 *= scale.y;
    mat.c2 *= scale.z;

    return mat;
}

// 获取几何体动画 alpha
inline float MdlGetGeosetAlpha(const MDLDATA& data, uint32_t geosetIndex, uint32_t time) {
    if (geosetIndex >= data.geosetAnimations.Count()) {
        return 1.0f;
    }

    const auto& geosetAnim = data.geosetAnimations[geosetIndex];

    // 将 MDLArray 包装为 MDLKEYTRACK 以便使用插值函数
    MDLKEYTRACK<MDLALPHAKEYFRAME> track;
    track.interpolationType = MDL_TRACKTYPE_LINEAR;
    track.keys = geosetAnim.alphaTrack;
    return MdlGetAlphaValue(track, time);
}
