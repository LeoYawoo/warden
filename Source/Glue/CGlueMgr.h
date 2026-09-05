#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CMainMenu;
class CCharacterSelection;
struct REALM_INFO;

// Reverse engineered from Warcraft III binary
// CGlueMgr manages the game's glue layer (login/menu screens)

class CGlueMgr {
public:
    CGlueMgr();
    ~CGlueMgr();

    // Manager operations
    static bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Screen management
    static void SetScreen(const char* screenName);
    static void SetCurrentScreen(const char* screenName);
    static void UpdateCurrentScreen(const char* screenName);
    static void SetLoginStateAndResult(int32_t state, int32_t result, const char* addrStr, const char* stateStr, const char* resultStr, uint32_t flags);
    void ShowMainMenu();
    void ShowCharacterSelection();
    void ShowLoadingScreen();
    void ShowScoreScreen();

    // Actions
    static void QuitGame();
    static void LoginServerLogin(const char* accountName, const char* password);
    static void StatusDialogClick();
    static void ChangeRealm(REALM_INFO *realmInfo);
    static void SetCurrentAccount(const char* accountName);

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
    static int32_t s_currentScreen;
    static CGlueMgr* s_instance;
    bool m_transitioning;
    CMainMenu* m_mainMenu;
    CCharacterSelection* m_characterSelection;
};
