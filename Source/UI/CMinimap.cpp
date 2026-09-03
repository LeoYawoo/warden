#include "CMinimap.h"

// Reverse engineered from Warcraft III binary

CMinimap::CMinimap() : m_width(200), m_height(200), m_visible(true), m_terrain(nullptr) {}
CMinimap::~CMinimap() {}

int32_t CMinimap::GetWidth() const { return m_width; }
int32_t CMinimap::GetHeight() const { return m_height; }

void CMinimap::SetSize(int32_t width, int32_t height) {
    m_width = width;
    m_height = height;
}

bool CMinimap::IsVisible() const { return m_visible; }
void CMinimap::SetVisible(bool visible) { m_visible = visible; }

CTerrain* CMinimap::GetTerrain() const { return m_terrain; }
void CMinimap::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
