#pragma once
// FreeType 2.x wrapper

#include <cstdint>

// Include actual FreeType headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H

// Custom wrapper functions
bool FREETYPE_RenderGlyph(uint32_t code, bool monochrome, FT_Face face);
void FreeTypeInitialize();

