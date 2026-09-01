#include "MapInfoFile.h"

// Reverse engineered from Warcraft III binary

MapInfoFile::MapInfoFile()
    : m_mapVersion(0),
      m_mapSize(0),
      m_mapFlags(0),
      m_valid(false) {
}

MapInfoFile::~MapInfoFile() {
}

const char* MapInfoFile::GetFileName() const {
    return m_fileName.c_str();
}

void MapInfoFile::SetFileName(const char* fileName) {
    if (fileName) {
        m_fileName = fileName;
    } else {
        m_fileName.clear();
    }
}

const char* MapInfoFile::GetMapName() const {
    return m_mapName.c_str();
}

void MapInfoFile::SetMapName(const char* name) {
    if (name) {
        m_mapName = name;
    } else {
        m_mapName.clear();
    }
}

const char* MapInfoFile::GetMapDescription() const {
    return m_mapDescription.c_str();
}

void MapInfoFile::SetMapDescription(const char* description) {
    if (description) {
        m_mapDescription = description;
    } else {
        m_mapDescription.clear();
    }
}

const char* MapInfoFile::GetAuthor() const {
    return m_author.c_str();
}

void MapInfoFile::SetAuthor(const char* author) {
    if (author) {
        m_author = author;
    } else {
        m_author.clear();
    }
}

int32_t MapInfoFile::GetMapVersion() const {
    return m_mapVersion;
}

void MapInfoFile::SetMapVersion(int32_t version) {
    m_mapVersion = version;
}

int32_t MapInfoFile::GetMapSize() const {
    return m_mapSize;
}

void MapInfoFile::SetMapSize(int32_t size) {
    m_mapSize = size;
}

int32_t MapInfoFile::GetMapFlags() const {
    return m_mapFlags;
}

void MapInfoFile::SetMapFlags(int32_t flags) {
    m_mapFlags = flags;
}

bool MapInfoFile::Load(const char* fileName) {
    if (!fileName) {
        return false;
    }

    m_fileName = fileName;
    // TODO: Implement file loading
    m_valid = true;
    return true;
}

bool MapInfoFile::Save(const char* fileName) {
    if (!fileName) {
        return false;
    }

    // TODO: Implement file saving
    return true;
}

bool MapInfoFile::IsValid() const {
    return m_valid;
}
