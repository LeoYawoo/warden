#include "CMdlModel.h"
#include <cstring>
#include <algorithm>

// ============================================================================
// 构造函数/析构函数
// ============================================================================

CMdlModel::CMdlModel()
    : m_data(new MDLDATA())
    , m_loaded(false)
    , m_currentAnim(0)
    , m_currentTime(0)
    , m_loop(true)
    , m_timeScale(1.0f) {
}

CMdlModel::~CMdlModel() {
    Release();
}

// ============================================================================
// 加载接口
// ============================================================================

bool CMdlModel::Load(const char* filePath, Status& status) {
    if (m_loaded) {
        Release();
    }

    MdlBinReader reader;
    if (!reader.ReadFile(filePath, *m_data, status)) {
        return false;
    }

    m_loaded = true;
    InitializeInterpolator();
    return true;
}

bool CMdlModel::LoadFromBuffer(const uint8_t* buffer, uint32_t size, Status& status) {
    if (m_loaded) {
        Release();
    }

    MsgBuffer msgBuffer(size);
    if (!msgBuffer.Write(buffer, size)) {
        status.SetError(-1, "Failed to copy buffer");
        delete m_data;
        m_data = nullptr;
        return false;
    }

    msgBuffer.Seek(0);

    MdlBinReader reader;
    if (!reader.Read(msgBuffer, *m_data, status)) {
        delete m_data;
        m_data = nullptr;
        return false;
    }

    m_loaded = true;
    InitializeInterpolator();
    return true;
}

void CMdlModel::Release() {
    if (m_data) {
        // 释放各 section 的数据
        auto ReleaseArray = [](auto& arr) {
            if (arr.offset != 0) {
                delete[] reinterpret_cast<void*>(arr.offset);
                arr.offset = 0;
                arr.count = 0;
            }
        };

        ReleaseArray(m_data->sequences);
        ReleaseArray(m_data->globalSequences);
        ReleaseArray(m_data->sounds);
        ReleaseArray(m_data->materials);
        ReleaseArray(m_data->textures);
        ReleaseArray(m_data->textureAnimations);
        ReleaseArray(m_data->geosets);
        ReleaseArray(m_data->geosetAnimations);
        ReleaseArray(m_data->bones);
        ReleaseArray(m_data->lights);
        ReleaseArray(m_data->helpers);
        ReleaseArray(m_data->soundEmitters);
        ReleaseArray(m_data->attachments);
        ReleaseArray(m_data->pivotPoints);
        ReleaseArray(m_data->particleEmitters);
        ReleaseArray(m_data->cameras);
        ReleaseArray(m_data->events);
        ReleaseArray(m_data->particleEmitters2);
        ReleaseArray(m_data->collisionShapes);
        ReleaseArray(m_data->ribbonEmitters);

        delete m_data;
        m_data = nullptr;
    }

    m_loaded = false;
    m_currentAnim = 0;
    m_currentTime = 0;
}

// ============================================================================
// 动画控制
// ============================================================================

void CMdlModel::SetAnimation(uint32_t animIndex) {
    if (!m_loaded) return;

    if (animIndex < m_data->sequences.Count()) {
        m_currentAnim = animIndex;
        m_currentTime = 0;
    }
}

void CMdlModel::SetTime(uint32_t time) {
    if (!m_loaded) return;

    m_currentTime = ClampTime(time);
}

void CMdlModel::Update(float deltaTime) {
    if (!m_loaded) return;

    if (m_data->sequences.Count() == 0) return;

    const auto& seq = m_data->sequences[m_currentAnim];
    uint32_t duration = seq.interval[1] - seq.interval[0];

    if (duration == 0) return;

    m_currentTime += static_cast<uint32_t>(deltaTime * 1000.0f * m_timeScale);

    if (m_loop) {
        m_currentTime = m_currentTime % duration;
    } else {
        if (m_currentTime >= duration) {
            m_currentTime = duration - 1;
        }
    }

    // 更新插值器
    m_interpolator.Update(m_currentTime + seq.interval[0]);
}

// ============================================================================
// 查询接口
// ============================================================================

const char* CMdlModel::GetName() const {
    if (!m_loaded || !m_data) return "";
    return m_data->header.name;
}

uint32_t CMdlModel::GetBoneCount() const {
    if (!m_loaded || !m_data) return 0;
    return m_data->bones.Count();
}

uint32_t CMdlModel::GetGeosetCount() const {
    if (!m_loaded || !m_data) return 0;
    return m_data->geosets.Count();
}

uint32_t CMdlModel::GetSequenceCount() const {
    if (!m_loaded || !m_data) return 0;
    return m_data->sequences.Count();
}

uint32_t CMdlModel::GetAnimationDuration() const {
    if (!m_loaded || !m_data) return 0;
    if (m_currentAnim >= m_data->sequences.Count()) return 0;

    const auto& seq = m_data->sequences[m_currentAnim];
    return seq.interval[1] - seq.interval[0];
}

CAaBox CMdlModel::GetBoundingBox() const {
    if (!m_loaded || !m_data) {
        return CAaBox();
    }

    // 使用模型全局边界
    CAaBox bounds;
    bounds.b = C3Vector(
        m_data->model.animationBounds[0],
        m_data->model.animationBounds[1],
        m_data->model.animationBounds[2]
    );
    bounds.t = C3Vector(
        m_data->model.animationBounds[3],
        m_data->model.animationBounds[4],
        m_data->model.animationBounds[5]
    );

    return bounds;
}

C44Matrix CMdlModel::GetBoneMatrix(uint32_t boneIndex) const {
    if (!m_loaded || !m_data) {
        return C44Matrix::Identity();
    }

    return m_interpolator.GetBoneMatrix(boneIndex);
}

float CMdlModel::GetGeosetAlpha(uint32_t geosetIndex) const {
    if (!m_loaded || !m_data) {
        return 1.0f;
    }

    return m_interpolator.GetGeosetAlpha(geosetIndex);
}

// ============================================================================
// 私有方法
// ============================================================================

void CMdlModel::InitializeInterpolator() {
    if (m_data) {
        m_interpolator.Initialize(*m_data);
    }
}

uint32_t CMdlModel::ClampTime(uint32_t time) const {
    if (!m_data || m_currentAnim >= m_data->sequences.Count()) {
        return 0;
    }

    const auto& seq = m_data->sequences[m_currentAnim];
    uint32_t duration = seq.interval[1] - seq.interval[0];

    if (duration == 0) return 0;

    if (m_loop) {
        return time % duration;
    } else {
        return std::min(time, duration - 1);
    }
}
