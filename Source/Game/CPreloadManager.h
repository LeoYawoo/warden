#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CPreloadManager manages preloading of game assets

class CPreloadManager {
public:
    CPreloadManager();
    ~CPreloadManager();

    // Preload operations
    void PreloadFile(const char* fileName);
    void PreloadAll();
    void CancelPreload();

    // Preload state
    bool IsPreloading() const;
    size_t GetPreloadCount() const;
    size_t GetPreloadedCount() const;

    // Preload properties
    void SetAutoPreload(bool autoPreload);
    bool IsAutoPreload() const;

protected:
    std::vector<std::string> m_preloadFiles;
    std::vector<std::string> m_preloadedFiles;
    bool m_preloading;
    bool m_autoPreload;
};
