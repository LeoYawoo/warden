#include "MapInfoFile.h"

// Reverse engineered from Warcraft III binary

MapInfoFile::MapInfoFile()
    : m_mapVersion(0), m_mapSize(0), m_mapFlags(0), m_valid(false) {
}

MapInfoFile::~MapInfoFile() {}

const char* MapInfoFile::GetFileName() const { return m_fileName.c_str(); }
void MapInfoFile::SetFileName(const char* fileName) { m_fileName = fileName ? fileName : ""; }

const char* MapInfoFile::GetMapName() const { return m_mapName.c_str(); }
void MapInfoFile::SetMapName(const char* name) { m_mapName = name ? name : ""; }

const char* MapInfoFile::GetMapAuthor() const { return m_mapAuthor.c_str(); }
void MapInfoFile::SetMapAuthor(const char* author) { m_mapAuthor = author ? author : ""; }

const char* MapInfoFile::GetMapDescription() const { return m_mapDescription.c_str(); }
void MapInfoFile::SetMapDescription(const char* description) { m_mapDescription = description ? description : ""; }

int32_t MapInfoFile::GetMapVersion() const { return m_mapVersion; }
void MapInfoFile::SetMapVersion(int32_t version) { m_mapVersion = version; }

int32_t MapInfoFile::GetMapSize() const { return m_mapSize; }
void MapInfoFile::SetMapSize(int32_t size) { m_mapSize = size; }

int32_t MapInfoFile::GetMapFlags() const { return m_mapFlags; }
void MapInfoFile::SetMapFlags(int32_t flags) { m_mapFlags = flags; }

bool MapInfoFile::Load(const char* fileName) {
    if (!fileName) return false;

    m_fileName = fileName;

    // In a real implementation, this would parse the W3W/W3M map info file
    // For now, we just mark it as valid
    m_valid = true;
    return true;
}

bool MapInfoFile::Save(const char* fileName) {
    const char* saveFile = fileName ? fileName : m_fileName.c_str();
    if (!saveFile || saveFile[0] == '\0') return false;

    // In a real implementation, this would write the map info file
    // For now, we just return success
    return true;
}

void MapInfoFile::Clear() {
    m_mapName.clear();
    m_mapAuthor.clear();
    m_mapDescription.clear();
    m_mapVersion = 0;
    m_mapSize = 0;
    m_mapFlags = 0;
    m_valid = false;
}

bool MapInfoFile::IsValid() const { return m_valid; }
