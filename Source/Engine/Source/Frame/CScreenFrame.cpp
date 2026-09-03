#include "CScreenFrame.h"

// Reverse engineered from Warcraft III binary

CScreenFrame::CScreenFrame() : m_screenWidth(800), m_screenHeight(600) {}
CScreenFrame::~CScreenFrame() {}

int32_t CScreenFrame::GetScreenWidth() const { return m_screenWidth; }
int32_t CScreenFrame::GetScreenHeight() const { return m_screenHeight; }

void CScreenFrame::SetScreenSize(int32_t width, int32_t height) {
    m_screenWidth = width;
    m_screenHeight = height;
    SetSize(static_cast<float>(width), static_cast<float>(height));
}
