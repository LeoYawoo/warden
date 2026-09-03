#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// MainApp manages the main application on Mac

class MainApp {
public:
    MainApp();
    ~MainApp();

    // Application operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Application properties
    const char* GetAppName() const;
    void SetAppName(const char* name);

    const char* GetVersion() const;
    void SetVersion(const char* version);

    // Application state
    bool IsRunning() const;
    void SetRunning(bool running);

protected:
    bool m_initialized;
    bool m_running;
    std::string m_appName;
    std::string m_version;
};
