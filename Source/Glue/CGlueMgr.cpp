#include "CGlueMgr.h"

// Reverse engineered from Warcraft III binary

CGlueMgr::CGlueMgr()
    : m_initialized(false), m_currentScreen(SCREEN_NONE),
      m_transitioning(false), m_mainMenu(nullptr),
      m_characterSelection(nullptr) {
}

CGlueMgr::~CGlueMgr() {
    Shutdown();
}

bool CGlueMgr::Initialize() {
    m_initialized = true;
    m_currentScreen = SCREEN_MAIN_MENU;
    return true;
}

void CGlueMgr::Shutdown() {
    m_initialized = false;
    m_currentScreen = SCREEN_NONE;
}

bool CGlueMgr::IsInitialized() const { return m_initialized; }

void CGlueMgr::ShowMainMenu() {
    m_currentScreen = SCREEN_MAIN_MENU;
}

void CGlueMgr::ShowCharacterSelection() {
    m_currentScreen = SCREEN_CHARACTER_SELECTION;
}

void CGlueMgr::ShowLoadingScreen() {
    m_currentScreen = SCREEN_LOADING;
}

void CGlueMgr::ShowScoreScreen() {
    m_currentScreen = SCREEN_SCORE;
}

int32_t CGlueMgr::GetCurrentScreen() const { return m_currentScreen; }

const char* CGlueMgr::GetCurrentScreenName() const {
    switch (m_currentScreen) {
        case SCREEN_MAIN_MENU: return "MainMenu";
        case SCREEN_CHARACTER_SELECTION: return "CharacterSelection";
        case SCREEN_LOADING: return "Loading";
        case SCREEN_SCORE: return "Score";
        case SCREEN_GAME: return "Game";
        default: return "None";
    }
}

bool CGlueMgr::IsTransitioning() const { return m_transitioning; }
