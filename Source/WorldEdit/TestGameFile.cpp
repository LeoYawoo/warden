#include "TestGameFile.h"

// Reverse engineered from Warcraft III binary

TestGameFile::TestGameFile() : m_loaded(false), m_valid(false) {}
TestGameFile::~TestGameFile() { Close(); }

const char* TestGameFile::GetFileName() const { return m_fileName.c_str(); }
void TestGameFile::SetFileName(const char* fileName) { m_fileName = fileName ? fileName : ""; }

bool TestGameFile::IsLoaded() const { return m_loaded; }
void TestGameFile::SetLoaded(bool loaded) { m_loaded = loaded; }

bool TestGameFile::IsValid() const { return m_valid; }

bool TestGameFile::Load(const char* fileName) {
    if (!fileName) return false;

    m_fileName = fileName;

    // In a real implementation, this would open and parse the test game file
    // For now, we just mark it as loaded
    m_loaded = true;
    m_valid = true;
    return true;
}

bool TestGameFile::Save(const char* fileName) {
    const char* saveFile = fileName ? fileName : m_fileName.c_str();
    if (!saveFile || saveFile[0] == '\0') return false;

    // In a real implementation, this would write the test game file
    // For now, we just return success
    return true;
}

void TestGameFile::Close() {
    m_loaded = false;
}
