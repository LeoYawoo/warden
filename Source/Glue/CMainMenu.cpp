#include "CMainMenu.h"

// Reverse engineered from Warcraft III binary

CMainMenu::CMainMenu() : m_initialized(false), m_visible(true), m_glueMgr(nullptr) {}
CMainMenu::~CMainMenu() { Shutdown(); }

bool CMainMenu::Initialize() {
    m_initialized = true;
    m_visible = true;
    return true;
}

void CMainMenu::Shutdown() {
    m_initialized = false;
}

bool CMainMenu::IsInitialized() const { return m_initialized; }

void CMainMenu::OnSinglePlayer() {
    // Show single player menu
    // In a full implementation, this would transition to the single player menu
    // and allow the user to select a campaign or custom game
}

void CMainMenu::OnMultiplayer() {
    // Show multiplayer menu
    // In a full implementation, this would transition to the multiplayer menu
    // and allow the user to connect to Battle.net or LAN
}

void CMainMenu::OnOptions() {
    // Show options menu
    // In a full implementation, this would transition to the options menu
    // and allow the user to configure game settings
}

void CMainMenu::OnCredits() {
    // Show credits
    // In a full implementation, this would display the game credits
}

void CMainMenu::OnQuit() {
    // Quit game
    // In a full implementation, this would exit the game
    // For now, we just set the visible flag to false
    m_visible = false;
}

bool CMainMenu::IsVisible() const { return m_visible; }
void CMainMenu::SetVisible(bool visible) { m_visible = visible; }
