#include "TestGameFile.h"

// Reverse engineered from Warcraft III binary

TestGameFile::TestGameFile() : m_loaded(false), m_valid(false) {}
TestGameFile::~TestGameFile() {}

const char* TestGameFile::GetFileName() const { return m_fileName.c_str(); }
void TestGameFile::SetFileName(const char* fileName) { m_fileName = fileName ? fileName : ""; }
bool TestGameFile::IsLoaded() const { return m_loaded; }
void TestGameFile::SetLoaded(bool loaded) { m_loaded = loaded; }
bool TestGameFile::IsValid() const { return m_valid; }

bool TestGameFile::Load(const char* fileName) {
    if (!fileName) return false;
    m_fileName = fileName;
    // TODO: Implement file loading
    m_loaded = true;
    m_valid = true;
    return true;
}

bool TestGameFile::Save(const char* fileName) {
    if (!fileName) return false;
    // TODO: Implement file saving
    return true;
}

void TestGameFile::Close() {
    m_loaded = false;
}
