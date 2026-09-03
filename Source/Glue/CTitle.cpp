#include "CTitle.h"

// Reverse engineered from Warcraft III binary

CTitle::CTitle() : m_initialized(false), m_visible(true) {}
CTitle::~CTitle() { Shutdown(); }

bool CTitle::Initialize() {
    m_initialized = true;
    m_visible = true;
    return true;
}

void CTitle::Shutdown() {
    m_initialized = false;
}

bool CTitle::IsInitialized() const { return m_initialized; }

const char* CTitle::GetTitle() const { return m_title.c_str(); }
void CTitle::SetTitle(const char* title) { m_title = title ? title : ""; }

const char* CTitle::GetSubtitle() const { return m_subtitle.c_str(); }
void CTitle::SetSubtitle(const char* subtitle) { m_subtitle = subtitle ? subtitle : ""; }

bool CTitle::IsVisible() const { return m_visible; }
void CTitle::SetVisible(bool visible) { m_visible = visible; }
