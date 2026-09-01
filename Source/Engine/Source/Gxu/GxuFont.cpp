#include "GxuFont.h"

// Reverse engineered from Warcraft III binary

GxuFont::GxuFont() : m_loaded(false), m_height(0.0f), m_scale(1.0f) {}
GxuFont::~GxuFont() { Unload(); }

bool GxuFont::Load(const char* fileName) {
    if (!fileName) return false;
    m_fontName = fileName;
    m_loaded = true;
    return true;
}

void GxuFont::Unload() {
    m_loaded = false;
    m_fontName.clear();
}

void GxuFont::BeginString(CGxStringBatch* batch) { (void)batch; }
void GxuFont::EndString() {}
float GxuFont::GetCharWidth(char ch) { (void)ch; return 0.0f; }
float GxuFont::GetCharHeight(char ch) { (void)ch; return m_height; }
float GxuFont::GetHeight() const { return m_height; }
float GxuFont::GetScale() const { return m_scale; }
void GxuFont::SetScale(float scale) { m_scale = scale; }
const char* GxuFont::GetFontName() const { return m_fontName.c_str(); }
void GxuFont::SetFontName(const char* name) { m_fontName = name ? name : ""; }
bool GxuFont::IsLoaded() const { return m_loaded; }
