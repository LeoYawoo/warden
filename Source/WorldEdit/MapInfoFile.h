#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// MapInfoFile manages map information files

class MapInfoFile {
public:
    MapInfoFile();
    ~MapInfoFile();

    // File properties
    const char* GetFileName() const;
    void SetFileName(const char* fileName);

    // Map properties
    const char* GetMapName() const;
    void SetMapName(const char* name);

    const char* GetMapAuthor() const;
    void SetMapAuthor(const char* author);

    const char* GetMapDescription() const;
    void SetMapDescription(const char* description);

    // Map settings
    int32_t GetMapVersion() const;
    void SetMapVersion(int32_t version);

    int32_t GetMapSize() const;
    void SetMapSize(int32_t size);

    int32_t GetMapFlags() const;
    void SetMapFlags(int32_t flags);

    // File operations
    bool Load(const char* fileName);
    bool Save(const char* fileName = nullptr);
    void Clear();

    // Validation
    bool IsValid() const;

protected:
    std::string m_fileName;
    std::string m_mapName;
    std::string m_mapAuthor;
    std::string m_mapDescription;
    int32_t m_mapVersion;
    int32_t m_mapSize;
    int32_t m_mapFlags;
    bool m_valid;
};
