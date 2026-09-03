#include "CGameUI.h"

// Reverse engineered from Warcraft III binary

CGameUI::CGameUI()
    : m_initialized(false), m_visible(true),
      m_resourceBar(nullptr), m_heroBar(nullptr),
      m_minimap(nullptr), m_commandBar(nullptr),
      m_chatVisible(false) {
}

CGameUI::~CGameUI() { Shutdown(); }

bool CGameUI::Initialize() {
    m_initialized = true;
    return true;
}

void CGameUI::Shutdown() {
    m_initialized = false;
}

bool CGameUI::IsInitialized() const { return m_initialized; }

bool CGameUI::IsVisible() const { return m_visible; }
void CGameUI::SetVisible(bool visible) { m_visible = visible; }

CResourceBar* CGameUI::GetResourceBar() const { return m_resourceBar; }
CHeroBar* CGameUI::GetHeroBar() const { return m_heroBar; }
CMinimap* CGameUI::GetMinimap() const { return m_minimap; }
CCommandBar* CGameUI::GetCommandBar() const { return m_commandBar; }

bool CGameUI::IsChatVisible() const { return m_chatVisible; }
void CGameUI::SetChatVisible(bool visible) { m_chatVisible = visible; }
