#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CInputObserver observes input events

class CInputObserver {
public:
    CInputObserver();
    ~CInputObserver();

    // Observer operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Input handling
    void OnKeyDown(int32_t key);
    void OnKeyUp(int32_t key);
    void OnMouseMove(int32_t x, int32_t y);
    void OnMouseButton(int32_t button, bool pressed);

protected:
    bool m_initialized;
};
