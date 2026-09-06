#include "MdlInterp.h"
#include <cstring>

// ============================================================================
// 构造函数/析构函数
// ============================================================================

MdlInterp::MdlInterp()
    : m_data(nullptr)
    , m_currentTime(0)
    , m_boneMatricesDirty(true)
    , m_geosetAlphasDirty(true) {
}

MdlInterp::~MdlInterp() {}

// ============================================================================
// 公共接口
// ============================================================================

void MdlInterp::Initialize(const MDLDATA& data) {
    m_data = &data;
    m_currentTime = 0;

    // 分配缓存空间
    m_boneMatrices.resize(data.bones.Count());
    m_geosetAlphas.resize(data.geosetAnimations.Count());

    m_boneMatricesDirty = true;
    m_geosetAlphasDirty = true;
}

void MdlInterp::Update(uint32_t time) {
    if (m_currentTime != time) {
        m_currentTime = time;
        m_boneMatricesDirty = true;
        m_geosetAlphasDirty = true;
    }
}

C44Matrix MdlInterp::GetBoneMatrix(uint32_t boneIndex) const {
    if (!m_data || boneIndex >= m_boneMatrices.size()) {
        return C44Matrix();
    }

    if (m_boneMatricesDirty) {
        RecalculateBoneMatrices();
        m_boneMatricesDirty = false;
    }

    return m_boneMatrices[boneIndex];
}

float MdlInterp::GetGeosetAlpha(uint32_t geosetIndex) const {
    if (!m_data || geosetIndex >= m_geosetAlphas.size()) {
        return 1.0f;
    }

    if (m_geosetAlphasDirty) {
        RecalculateGeosetAlphas();
        m_geosetAlphasDirty = false;
    }

    return m_geosetAlphas[geosetIndex];
}

C44Matrix MdlInterp::GetTextureTransform(uint32_t texAnimIndex) const {
    // TODO: 实现纹理动画变换
    return C44Matrix();
}

// ============================================================================
// 私有函数
// ============================================================================

void MdlInterp::RecalculateBoneMatrices() const {
    if (!m_data) return;

    for (uint32_t i = 0; i < m_data->bones.Count(); i++) {
        const auto& bone = m_data->bones[i];

        // 计算本地变换
        C44Matrix localTransform = CalculateBoneLocalTransform(bone);

        // 如果有父骨骼，应用父骨骼变换
        if (bone.parentBone >= 0 && bone.parentBone < static_cast<int32_t>(m_data->bones.Count())) {
            C44Matrix parentMatrix = m_boneMatrices[bone.parentBone];
            m_boneMatrices[i] = parentMatrix * localTransform;
        } else {
            m_boneMatrices[i] = localTransform;
        }
    }
}

void MdlInterp::RecalculateGeosetAlphas() const {
    if (!m_data) return;

    for (uint32_t i = 0; i < m_data->geosetAnimations.Count(); i++) {
        const auto& geosetAnim = m_data->geosetAnimations[i];
        MDLKEYTRACK<MDLALPHAKEYFRAME> track;
        track.interpolationType = MDL_TRACKTYPE_LINEAR;
        track.keys = geosetAnim.alphaTrack;
        m_geosetAlphas[i] = MdlGetAlphaValue(track, m_currentTime);
    }
}

C44Matrix MdlInterp::CalculateBoneLocalTransform(const MDLBONESECTION& bone) const {
    // 获取动画值
    C3Vector translation = MdlGetTransValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLTRANSKEYFRAME>*>(&bone.translationTrack),
        m_currentTime
    );

    MDLROTKEYFRAME rotation = MdlGetRotValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLROTKEYFRAME>*>(&bone.rotationTrack),
        m_currentTime
    );

    C3Vector scale = MdlGetScaleValue(
        *reinterpret_cast<const MDLKEYTRACK<MDLSCALEKEYFRAME>*>(&bone.scaleTrack),
        m_currentTime
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
