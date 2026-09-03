#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CGlueMgr;

// Reverse engineered from Warcraft III binary
// CMainMenu manages the main menu screen

class CMainMenu {
public:
    CMainMenu();
    ~CMainMenu();

    // Menu operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Menu actions
    void OnSinglePlayer();
    void OnMultiplayer();
    void OnOptions();
    void OnCredits();
    void OnQuit();

    // Menu state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    bool m_initialized;
    bool m_visible;
    CGlueMgr* m_glueMgr;
};
