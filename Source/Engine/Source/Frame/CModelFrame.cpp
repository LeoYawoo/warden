#include "CModelFrame.h"
#include "../Anim/CMdlModel.h"
#include "../Base/Status.h"

// Reverse engineered from Warcraft III binary

CModelFrame::CModelFrame()
    : m_playing(false)
    , m_animation(0)
    , m_scale(1.0f)
    , m_mdlModel(nullptr) {
}

CModelFrame::~CModelFrame() {
    ReleaseMdlModel();
}

const char* CModelFrame::GetModelFile() const { return m_modelFile.c_str(); }

void CModelFrame::SetModelFile(const char* file) {
    if (file) {
        m_modelFile = file;

        // 检查是否是 MDL/MDX 文件
        std::string ext = file;
        size_t pos = ext.rfind('.');
        if (pos != std::string::npos) {
            ext = ext.substr(pos);
            // 转换为小写
            for (auto& c : ext) {
                c = static_cast<char>(std::tolower(c));
            }

            if (ext == ".mdx" || ext == ".mdl") {
                LoadMdlModel(file);
            }
        }
    } else {
        m_modelFile.clear();
        ReleaseMdlModel();
    }
}

bool CModelFrame::IsPlaying() const { return m_playing; }

void CModelFrame::SetPlaying(bool playing) {
    m_playing = playing;
    if (m_mdlModel) {
        // MDL 模型播放控制
        if (playing) {
            m_mdlModel->SetTime(0);
        }
    }
}

void CModelFrame::SetAnimation(int32_t animId) {
    m_animation = animId;
    if (m_mdlModel) {
        m_mdlModel->SetAnimation(static_cast<uint32_t>(animId));
    }
}

int32_t CModelFrame::GetAnimation() const { return m_animation; }

float CModelFrame::GetScale() const { return m_scale; }

void CModelFrame::SetScale(float scale) { m_scale = scale; }

void CModelFrame::Update(float deltaTime) {
    if (m_playing && m_mdlModel) {
        m_mdlModel->Update(deltaTime);
    }
}

bool CModelFrame::LoadMdlModel(const char* filePath) {
    // 释放旧模型
    ReleaseMdlModel();

    // 创建新模型
    m_mdlModel = new CMdlModel();

    Status status;
    if (!m_mdlModel->Load(filePath, status)) {
        delete m_mdlModel;
        m_mdlModel = nullptr;
        return false;
    }

    return true;
}

void CModelFrame::ReleaseMdlModel() {
    if (m_mdlModel) {
        delete m_mdlModel;
        m_mdlModel = nullptr;
    }
}
