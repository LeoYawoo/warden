#include "JassWar3.h"

// Reverse engineered from Warcraft III binary

JassWar3::JassWar3() : m_initialized(false), m_scriptLoaded(false) {}
JassWar3::~JassWar3() { Shutdown(); }

bool JassWar3::Initialize() {
    m_initialized = true;
    return true;
}

void JassWar3::Shutdown() {
    m_initialized = false;
    m_scriptLoaded = false;
}

bool JassWar3::IsInitialized() const { return m_initialized; }

bool JassWar3::ExecuteScript(const char* script) {
    if (!script) return false;
    // TODO: Implement script execution
    return true;
}

bool JassWar3::LoadScript(const char* fileName) {
    if (!fileName) return false;
    m_scriptName = fileName;
    m_scriptLoaded = true;
    return true;
}

bool JassWar3::IsScriptLoaded() const { return m_scriptLoaded; }
