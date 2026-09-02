#include "CWar3Image.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary
// Address: 0x85AFD3

CWar3Image::CWar3Image()
    : m_imageId(0),
      m_width(0),
      m_height(0),
      m_loaded(false),
      m_data(nullptr) {
}

CWar3Image::~CWar3Image() {
    Unload();
}

int32_t CWar3Image::GetImageId() const {
    return m_imageId;
}

void CWar3Image::SetImageId(int32_t id) {
    m_imageId = id;
}

const char* CWar3Image::GetImageName() const {
    return m_imageName.c_str();
}

void CWar3Image::SetImageName(const char* name) {
    if (name) {
        m_imageName = name;
    } else {
        m_imageName.clear();
    }
}

uint32_t CWar3Image::GetWidth() const {
    return m_width;
}

uint32_t CWar3Image::GetHeight() const {
    return m_height;
}

void CWar3Image::SetSize(uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
}

bool CWar3Image::Load(const char* fileName) {
    if (!fileName) return false;

    Unload();
    m_imageName = fileName;

    // TODO: Implement actual image loading
    m_loaded = true;
    return true;
}

void CWar3Image::Unload() {
    if (m_data) {
        SMemFree(m_data, __FILE__, __LINE__, 0);
        m_data = nullptr;
    }
    m_loaded = false;
    m_width = 0;
    m_height = 0;
}

bool CWar3Image::IsLoaded() const {
    return m_loaded;
}
