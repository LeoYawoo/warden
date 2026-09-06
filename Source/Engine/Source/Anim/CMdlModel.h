#pragma once

#include "MdlData.h"
#include "MdlBinReader.h"
#include "MdlInterp.h"
#include "MdlKeyTrack.h"
#include "../Base/Status.h"
#include "../Tempest/C44Matrix.h"
#include "../Tempest/C3Vector.h"
#include "../Tempest/CAaBox.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace Tempest;

// ============================================================================
// CMdlModel - WC3 MDL 模型类
// 负责加载、动画和渲染 MDX/MDL 模型文件
// ============================================================================

class CMdlModel {
public:
    CMdlModel();
    ~CMdlModel();

    // 禁止拷贝
    CMdlModel(const CMdlModel&) = delete;
    CMdlModel& operator=(const CMdlModel&) = delete;

    // 加载模型
    bool Load(const char* filePath, Status& status);
    bool LoadFromBuffer(const uint8_t* buffer, uint32_t size, Status& status);

    // 释放资源
    void Release();

    // 动画控制
    void SetAnimation(uint32_t animIndex);
    uint32_t GetAnimation() const { return m_currentAnim; }

    void SetTime(uint32_t time);
    uint32_t GetTime() const { return m_currentTime; }

    void SetLoop(bool loop) { m_loop = loop; }
    bool GetLoop() const { return m_loop; }

    // 更新动画
    void Update(float deltaTime);

    // 获取模型信息
    const char* GetName() const;
    uint32_t GetBoneCount() const;
    uint32_t GetGeosetCount() const;
    uint32_t GetSequenceCount() const;
    uint32_t GetAnimationDuration() const;

    // 获取包围盒
    CAaBox GetBoundingBox() const;

    // 获取骨骼变换
    C44Matrix GetBoneMatrix(uint32_t boneIndex) const;

    // 获取几何体动画 alpha
    float GetGeosetAlpha(uint32_t geosetIndex) const;

    // 获取原始数据 (用于渲染)
    const MDLDATA* GetData() const { return m_data; }

    // 检查是否已加载
    bool IsLoaded() const { return m_loaded; }

private:
    // 模型数据
    MDLDATA* m_data;
    bool m_loaded;

    // 动画状态
    uint32_t m_currentAnim;
    uint32_t m_currentTime;
    bool m_loop;
    float m_timeScale;

    // 动画插值器
    MdlInterp m_interpolator;

    // 内部方法
    void InitializeInterpolator();
    uint32_t ClampTime(uint32_t time) const;
};
