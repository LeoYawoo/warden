#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CMainMenu;
class CCharacterSelection;

// Reverse engineered from Warcraft III binary
// CGlueMgr manages the game's glue layer (login/menu screens)

class CGlueMgr {
public:
    CGlueMgr();
    ~CGlueMgr();

    // Manager operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Screen management
    void ShowMainMenu();
    void ShowCharacterSelection();
    void ShowLoadingScreen();
    void ShowScoreScreen();

    // Screen properties
    int32_t GetCurrentScreen() const;
    const char* GetCurrentScreenName() const;

    // Manager state
    bool IsTransitioning() const;

    // Screen types
    enum Screen {
        SCREEN_NONE = 0,
        SCREEN_MAIN_MENU = 1,
        SCREEN_CHARACTER_SELECTION = 2,
        SCREEN_LOADING = 3,
        SCREEN_SCORE = 4,
        SCREEN_GAME = 5
    };

protected:
    bool m_initialized;
    int32_t m_currentScreen;
    bool m_transitioning;
    CMainMenu* m_mainMenu;
    CCharacterSelection* m_characterSelection;
};
