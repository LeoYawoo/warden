#pragma once

#include "IGxuFont.h"
#include <string>

// Forward declarations
struct CGxStringBatch;

// Reverse engineered from Warcraft III binary
// GxuFont implements font rendering

class GxuFont : public IGxuFont {
public:
    GxuFont();
    virtual ~GxuFont();

    // IGxuFont interface
    bool Load(const char* fileName) override;
    void Unload() override;

    void BeginString(CGxStringBatch* batch) override;
    void EndString() override;

    float GetCharWidth(char ch) override;
    float GetCharHeight(char ch) override;

    float GetHeight() const override;
    float GetScale() const override;
    void SetScale(float scale) override;

    // Additional font operations
    const char* GetFontName() const;
    void SetFontName(const char* name);

    bool IsLoaded() const;

protected:
    std::string m_fontName;
    bool m_loaded;
    float m_height;
    float m_scale;
};
