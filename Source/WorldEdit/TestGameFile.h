#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// TestGameFile manages test game files

class TestGameFile {
public:
    TestGameFile();
    ~TestGameFile();

    // File properties
    const char* GetFileName() const;
    void SetFileName(const char* fileName);

    // File state
    bool IsLoaded() const;
    void SetLoaded(bool loaded);

    bool IsValid() const;

    // File operations
    bool Load(const char* fileName);
    bool Save(const char* fileName = nullptr);
    void Close();

protected:
    std::string m_fileName;
    bool m_loaded;
    bool m_valid;
};
