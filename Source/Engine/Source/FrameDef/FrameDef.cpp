#include "FrameDef.h"

// Reverse engineered from Warcraft III binary

FrameDef::FrameDef()
    : m_frameId(0),
      m_parent(nullptr),
      m_child(nullptr),
      m_next(nullptr) {
    m_type = 0;
    m_enabled = true;
}

FrameDef::~FrameDef() {
}

const char* FrameDef::GetName() const {
    return m_name.c_str();
}

void FrameDef::SetName(const char* name) {
    if (name) {
        m_name = name;
    } else {
        m_name.clear();
    }
}

int32_t FrameDef::GetType() const {
    return m_type;
}

void FrameDef::SetType(int32_t type) {
    m_type = type;
}

bool FrameDef::IsEnabled() const {
    return m_enabled;
}

void FrameDef::SetEnabled(bool enabled) {
    m_enabled = enabled;
}

CFrame* FrameDef::CreateFrame() {
    // Create a new frame based on this frame definition
    // In a real implementation, this would create a CFrame instance
    // and initialize it with the properties from this FrameDef
    return nullptr; // Placeholder
}

void FrameDef::DestroyFrame(CFrame* frame) {
    // Destroy a frame created from this frame definition
    // In a real implementation, this would clean up the frame
    // and release any resources it holds
    (void)frame;
}

int32_t FrameDef::GetFrameId() const {
    return m_frameId;
}

void FrameDef::SetFrameId(int32_t id) {
    m_frameId = id;
}

const char* FrameDef::GetParentName() const {
    return m_parentName.c_str();
}

void FrameDef::SetParentName(const char* name) {
    if (name) {
        m_parentName = name;
    } else {
        m_parentName.clear();
    }
}

FrameDef* FrameDef::GetParent() const {
    return m_parent;
}

void FrameDef::SetParent(FrameDef* parent) {
    m_parent = parent;
}

FrameDef* FrameDef::GetChild() const {
    return m_child;
}

void FrameDef::SetChild(FrameDef* child) {
    m_child = child;
}

FrameDef* FrameDef::GetNext() const {
    return m_next;
}

void FrameDef::SetNext(FrameDef* next) {
    m_next = next;
}
