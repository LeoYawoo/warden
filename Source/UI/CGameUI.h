#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CResourceBar;
class CHeroBar;
class CMinimap;
class CCommandBar;

// Reverse engineered from Warcraft III binary
// CGameUI manages the game user interface

class CGameUI {
public:
    CGameUI();
    ~CGameUI();

    // UI operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // UI visibility
    bool IsVisible() const;
    void SetVisible(bool visible);

    // UI components
    CResourceBar* GetResourceBar() const;
    CHeroBar* GetHeroBar() const;
    CMinimap* GetMinimap() const;
    CCommandBar* GetCommandBar() const;

    // UI state
    bool IsChatVisible() const;
    void SetChatVisible(bool visible);

protected:
    bool m_initialized;
    bool m_visible;
    CResourceBar* m_resourceBar;
    CHeroBar* m_heroBar;
    CMinimap* m_minimap;
    CCommandBar* m_commandBar;
    bool m_chatVisible;
};
