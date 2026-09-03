#include "WorldLoad.h"

// Reverse engineered from Warcraft III binary

WorldLoad::WorldLoad() : m_initialized(false), m_loading(false), m_progress(0.0f) {}
WorldLoad::~WorldLoad() { Shutdown(); }

bool WorldLoad::Initialize() {
    m_initialized = true;
    return true;
}

void WorldLoad::Shutdown() {
    m_initialized = false;
    m_loading = false;
}

bool WorldLoad::IsInitialized() const { return m_initialized; }

const char* WorldLoad::GetMapFile() const { return m_mapFile.c_str(); }
void WorldLoad::SetMapFile(const char* file) { m_mapFile = file ? file : ""; }

bool WorldLoad::IsLoading() const { return m_loading; }
void WorldLoad::SetLoading(bool loading) { m_loading = loading; }

float WorldLoad::GetProgress() const { return m_progress; }
void WorldLoad::SetProgress(float progress) { m_progress = progress; }

bool WorldLoad::LoadMap(const char* mapFile) {
    if (!mapFile) return false;
    m_mapFile = mapFile;
    m_loading = true;
    m_progress = 0.0f;
    // TODO: Implement actual map loading
    m_progress = 1.0f;
    m_loading = false;
    return true;
}

void WorldLoad::CancelLoad() {
    m_loading = false;
    m_progress = 0.0f;
}
