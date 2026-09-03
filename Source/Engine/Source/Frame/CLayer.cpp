#include "CLayer.h"
#include "CSimpleFrame.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CLayer::CLayer() : m_layerId(0), m_visible(true) {}
CLayer::~CLayer() {}

int32_t CLayer::GetLayerId() const { return m_layerId; }
void CLayer::SetLayerId(int32_t id) { m_layerId = id; }

const char* CLayer::GetLayerName() const { return m_layerName.c_str(); }
void CLayer::SetLayerName(const char* name) { m_layerName = name ? name : ""; }

bool CLayer::IsVisible() const { return m_visible; }
void CLayer::SetVisible(bool visible) { m_visible = visible; }

void CLayer::AddFrame(CSimpleFrame* frame) {
    if (frame) m_frames.push_back(frame);
}

void CLayer::RemoveFrame(CSimpleFrame* frame) {
    auto it = std::find(m_frames.begin(), m_frames.end(), frame);
    if (it != m_frames.end()) {
        m_frames.erase(it);
    }
}

size_t CLayer::GetFrameCount() const { return m_frames.size(); }

CSimpleFrame* CLayer::GetFrame(size_t index) const {
    if (index < m_frames.size()) return m_frames[index];
    return nullptr;
}

void CLayer::Update(float deltaTime) {
    if (!m_visible) return;
    for (auto* frame : m_frames) {
        frame->Update(deltaTime);
    }
}

void CLayer::Render() {
    if (!m_visible) return;
    for (auto* frame : m_frames) {
        frame->Render();
    }
}
