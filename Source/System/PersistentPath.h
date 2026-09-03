#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// PersistentPath manages persistent file paths

class PersistentPath {
public:
    PersistentPath();
    ~PersistentPath();

    // Path operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Path properties
    const char* GetBasePath() const;
    void SetBasePath(const char* path);

    const char* GetUserDataPath() const;
    void SetUserDataPath(const char* path);

    const char* GetSavePath() const;
    void SetSavePath(const char* path);

    // Path utilities
    bool FileExists(const char* fileName) const;
    bool CreateDirectory(const char* dirName) const;
    bool DeleteFile(const char* fileName) const;

protected:
    bool m_initialized;
    std::string m_basePath;
    std::string m_userDataPath;
    std::string m_savePath;
};
