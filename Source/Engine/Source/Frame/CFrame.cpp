#include "CFrame.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CFrame::CFrame()
    : m_frameId(0), m_visible(true), m_enabled(true),
      m_x(0), m_y(0), m_width(0), m_height(0), m_parent(nullptr) {
}

CFrame::~CFrame() {
    // Don't delete children - they are managed externally
    m_children.clear();
}

int32_t CFrame::GetFrameId() const { return m_frameId; }
void CFrame::SetFrameId(int32_t id) { m_frameId = id; }

const char* CFrame::GetFrameName() const { return m_frameName.c_str(); }
void CFrame::SetFrameName(const char* name) { m_frameName = name ? name : ""; }

bool CFrame::IsVisible() const { return m_visible; }
void CFrame::SetVisible(bool visible) { m_visible = visible; }

float CFrame::GetX() const { return m_x; }
float CFrame::GetY() const { return m_y; }
void CFrame::SetPosition(float x, float y) { m_x = x; m_y = y; }

float CFrame::GetWidth() const { return m_width; }
float CFrame::GetHeight() const { return m_height; }
void CFrame::SetSize(float width, float height) { m_width = width; m_height = height; }

bool CFrame::IsEnabled() const { return m_enabled; }
void CFrame::SetEnabled(bool enabled) { m_enabled = enabled; }

CFrame* CFrame::GetParent() const { return m_parent; }
void CFrame::SetParent(CFrame* parent) { m_parent = parent; }

void CFrame::AddChild(CFrame* child) {
    if (child) {
        child->SetParent(this);
        m_children.push_back(child);
    }
}

void CFrame::RemoveChild(CFrame* child) {
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        (*it)->SetParent(nullptr);
        m_children.erase(it);
    }
}

size_t CFrame::GetChildCount() const { return m_children.size(); }

CFrame* CFrame::GetChild(size_t index) const {
    if (index < m_children.size()) return m_children[index];
    return nullptr;
}

CFrame* CFrame::GetChildByName(const char* name) const {
    if (!name) return nullptr;
    for (auto* child : m_children) {
        if (child->GetFrameName() == name) return child;
    }
    return nullptr;
}

void CFrame::Update(float deltaTime) {
    (void)deltaTime;
    for (auto* child : m_children) {
        if (child->IsVisible()) {
            child->Update(deltaTime);
        }
    }
}

void CFrame::Render() {
    for (auto* child : m_children) {
        if (child->IsVisible()) {
            child->Render();
        }
    }
}

bool CFrame::HandleInput(int32_t message, int32_t wParam, int32_t lParam) {
    (void)message; (void)wParam; (void)lParam;
    return false;
}
