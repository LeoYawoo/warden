#include "CTextFrame.h"

// Reverse engineered from Warcraft III binary

CTextFrame::CTextFrame() : m_font(nullptr), m_hJust(0), m_vJust(0), m_color(0xFFFFFFFF) {}
CTextFrame::~CTextFrame() {}

const char* CTextFrame::GetText() const { return m_text.c_str(); }
void CTextFrame::SetText(const char* text) { m_text = text ? text : ""; }

CFont* CTextFrame::GetFont() const { return m_font; }
void CTextFrame::SetFont(CFont* font) { m_font = font; }

int32_t CTextFrame::GetHJust() const { return m_hJust; }
void CTextFrame::SetHJust(int32_t just) { m_hJust = just; }

int32_t CTextFrame::GetVJust() const { return m_vJust; }
void CTextFrame::SetVJust(int32_t just) { m_vJust = just; }

uint32_t CTextFrame::GetColor() const { return m_color; }
void CTextFrame::SetColor(uint32_t color) { m_color = color; }
