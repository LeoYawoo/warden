#include "CPreloadManager.h"

// Reverse engineered from Warcraft III binary

CPreloadManager::CPreloadManager() : m_preloading(false), m_autoPreload(true) {}
CPreloadManager::~CPreloadManager() { CancelPreload(); }

void CPreloadManager::PreloadFile(const char* fileName) {
    if (fileName) {
        m_preloadFiles.push_back(fileName);
    }
}

void CPreloadManager::PreloadAll() {
    m_preloading = true;
    // Preload all files in the preload list
    for (const auto& file : m_preloadFiles) {
        m_preloadedFiles.push_back(file);
    }
    m_preloading = false;
}

void CPreloadManager::CancelPreload() {
    m_preloading = false;
    m_preloadFiles.clear();
}

bool CPreloadManager::IsPreloading() const { return m_preloading; }

size_t CPreloadManager::GetPreloadCount() const { return m_preloadFiles.size(); }

size_t CPreloadManager::GetPreloadedCount() const { return m_preloadedFiles.size(); }

void CPreloadManager::SetAutoPreload(bool autoPreload) { m_autoPreload = autoPreload; }
bool CPreloadManager::IsAutoPreload() const { return m_autoPreload; }
