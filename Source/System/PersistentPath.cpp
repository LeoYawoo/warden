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
    (void)fileName;
    // TODO: Implement file existence check
    return false;
}

bool PersistentPath::CreateDirectory(const char* dirName) const {
    (void)dirName;
    // TODO: Implement directory creation
    return true;
}

bool PersistentPath::DeleteFile(const char* fileName) const {
    (void)fileName;
    // TODO: Implement file deletion
    return true;
}
