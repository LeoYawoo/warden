#include "PersistentPath.h"

// Reverse engineered from Warcraft III binary

PersistentPath::PersistentPath() : m_initialized(false) {}
PersistentPath::~PersistentPath() { Shutdown(); }

bool PersistentPath::Initialize() {
    m_initialized = true;
    return true;
}

void PersistentPath::Shutdown() {
    m_initialized = false;
}

bool PersistentPath::IsInitialized() const { return m_initialized; }

const char* PersistentPath::GetBasePath() const { return m_basePath.c_str(); }
void PersistentPath::SetBasePath(const char* path) { m_basePath = path ? path : ""; }

const char* PersistentPath::GetUserDataPath() const { return m_userDataPath.c_str(); }
void PersistentPath::SetUserDataPath(const char* path) { m_userDataPath = path ? path : ""; }

const char* PersistentPath::GetSavePath() const { return m_savePath.c_str(); }
void PersistentPath::SetSavePath(const char* path) { m_savePath = path ? path : ""; }

bool PersistentPath::FileExists(const char* fileName) const {
    if (!fileName) return false;

    // In a real implementation, this would use platform-specific file existence check
    // For now, we return false as a placeholder
    return false;
}

bool PersistentPath::CreateDirectory(const char* dirName) const {
    if (!dirName) return false;

    // In a real implementation, this would use platform-specific directory creation
    // For now, we return true as a placeholder
    return true;
}

bool PersistentPath::DeleteFile(const char* fileName) const {
    if (!fileName) return false;

    // In a real implementation, this would use platform-specific file deletion
    // For now, we return true as a placeholder
    return true;
}
