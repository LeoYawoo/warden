#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CAgent;

// Reverse engineered from Warcraft III binary
// Address: 0x85AFD3
// CWar3Image represents an image in Warcraft III

class CWar3Image {
public:
    CWar3Image();
    virtual ~CWar3Image();

    // Image properties
    int32_t GetImageId() const;
    void SetImageId(int32_t id);

    const char* GetImageName() const;
    void SetImageName(const char* name);

    // Image dimensions
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    void SetSize(uint32_t width, uint32_t height);

    // Image data
    bool Load(const char* fileName);
    void Unload();

    // Image state
    bool IsLoaded() const;

protected:
    int32_t m_imageId;
    std::string m_imageName;
    uint32_t m_width;
    uint32_t m_height;
    bool m_loaded;
    void* m_data;
};
