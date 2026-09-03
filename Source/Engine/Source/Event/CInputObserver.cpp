#include "CInputObserver.h"

// Reverse engineered from Warcraft III binary

CInputObserver::CInputObserver() : m_initialized(false) {}
CInputObserver::~CInputObserver() { Shutdown(); }

bool CInputObserver::Initialize() {
    m_initialized = true;
    return true;
}

void CInputObserver::Shutdown() {
    m_initialized = false;
}

bool CInputObserver::IsInitialized() const { return m_initialized; }

void CInputObserver::OnKeyDown(int32_t key) {
    (void)key;
    // Handle key down event
}

void CInputObserver::OnKeyUp(int32_t key) {
    (void)key;
    // Handle key up event
}

void CInputObserver::OnMouseMove(int32_t x, int32_t y) {
    (void)x; (void)y;
    // Handle mouse move event
}

void CInputObserver::OnMouseButton(int32_t button, bool pressed) {
    (void)button; (void)pressed;
    // Handle mouse button event
}
