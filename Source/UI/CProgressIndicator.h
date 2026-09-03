#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CProgressIndicator displays progress

class CProgressIndicator {
public:
    CProgressIndicator();
    ~CProgressIndicator();

    // Progress properties
    float GetProgress() const;
    void SetProgress(float progress);

    // Progress state
    bool IsVisible() const;
    void SetVisible(bool visible);

    bool IsAnimating() const;
    void SetAnimating(bool animating);

protected:
    float m_progress;
    bool m_visible;
    bool m_animating;
};
