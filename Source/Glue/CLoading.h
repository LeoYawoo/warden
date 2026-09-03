#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CLoading manages the loading screen

class CLoading {
public:
    CLoading();
    ~CLoading();

    // Loading operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Loading progress
    float GetProgress() const;
    void SetProgress(float progress);

    const char* GetStatusMessage() const;
    void SetStatusMessage(const char* message);

    // Loading state
    bool IsLoading() const;
    void SetLoading(bool loading);

protected:
    bool m_initialized;
    bool m_loading;
    float m_progress;
    std::string m_statusMessage;
};
