#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// WorldLoad manages world loading

class WorldLoad {
public:
    WorldLoad();
    ~WorldLoad();

    // Load operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Load properties
    const char* GetMapFile() const;
    void SetMapFile(const char* file);

    // Load state
    bool IsLoading() const;
    void SetLoading(bool loading);

    float GetProgress() const;
    void SetProgress(float progress);

    // Load control
    bool LoadMap(const char* mapFile);
    void CancelLoad();

protected:
    bool m_initialized;
    bool m_loading;
    float m_progress;
    std::string m_mapFile;
};
