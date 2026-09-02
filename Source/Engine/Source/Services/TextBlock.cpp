#include "TextBlock.h"

// Reverse engineered from Warcraft III binary

TextBlock::TextBlock()
    : m_maxWidth(0), m_font(nullptr), m_hJust(0), m_vJust(0), m_width(0), m_height(0) {}

TextBlock::~TextBlock() {}

void TextBlock::SetText(const char* text) {
    if (text) m_text = text;
}

const char* TextBlock::GetText() const {
    return m_text.c_str();
}

float TextBlock::GetWidth() const {
    return m_width;
}

float TextBlock::GetHeight() const {
    return m_height;
}

void TextBlock::SetMaxWidth(float maxWidth) {
    m_maxWidth = maxWidth;
}

void TextBlock::SetFont(CFont* font) {
    m_font = font;
}

CFont* TextBlock::GetFont() const {
    return m_font;
}

int32_t TextBlock::GetHJust() const {
    return m_hJust;
}

void TextBlock::SetHJust(int32_t just) {
    m_hJust = just;
}

int32_t TextBlock::GetVJust() const {
    return m_vJust;
}

void TextBlock::SetVJust(int32_t just) {
    m_vJust = just;
}

void TextBlock::Update() {
    // TODO: Implement text block update
    m_width = 0;
    m_height = 0;
}
