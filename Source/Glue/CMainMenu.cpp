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
    // TODO: Show single player menu
}

void CMainMenu::OnMultiplayer() {
    // TODO: Show multiplayer menu
}

void CMainMenu::OnOptions() {
    // TODO: Show options menu
}

void CMainMenu::OnCredits() {
    // TODO: Show credits
}

void CMainMenu::OnQuit() {
    // TODO: Quit game
}

bool CMainMenu::IsVisible() const { return m_visible; }
void CMainMenu::SetVisible(bool visible) { m_visible = visible; }
