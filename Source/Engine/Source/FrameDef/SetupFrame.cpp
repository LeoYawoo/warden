#include "SetupFrame.h"
#include "FrameDef.h"

// Reverse engineered from Warcraft III binary

SetupFrame::SetupFrame()
    : m_setupId(0),
      m_complete(false),
      m_frameDef(nullptr) {
}

SetupFrame::~SetupFrame() {
}

int32_t SetupFrame::GetSetupId() const {
    return m_setupId;
}

void SetupFrame::SetSetupId(int32_t id) {
    m_setupId = id;
}

const char* SetupFrame::GetSetupName() const {
    return m_setupName.c_str();
}

void SetupFrame::SetSetupName(const char* name) {
    if (name) {
        m_setupName = name;
    } else {
        m_setupName.clear();
    }
}

bool SetupFrame::IsComplete() const {
    return m_complete;
}

void SetupFrame::SetComplete(bool complete) {
    m_complete = complete;
}

bool SetupFrame::Setup(FrameDef* frameDef) {
    if (!frameDef) return false;

    m_frameDef = frameDef;
    m_complete = true;
    return true;
}

void SetupFrame::Reset() {
    m_complete = false;
    m_frameDef = nullptr;
}

void SetupFrame::SetParameter(const char* key, const char* value) {
    if (!key || !value) return;

    // Store parameter in internal map
    // In a real implementation, this would use a hash map or similar structure
    // For now, we just store the first parameter
    m_parameters[key] = value;
}

const char* SetupFrame::GetParameter(const char* key) const {
    if (!key) return nullptr;

    auto it = m_parameters.find(key);
    if (it != m_parameters.end()) {
        return it->second.c_str();
    }
    return nullptr;
}
