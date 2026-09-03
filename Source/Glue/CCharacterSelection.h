#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CCharacterSelection manages character selection

class CCharacterSelection {
public:
    CCharacterSelection();
    ~CCharacterSelection();

    // Selection operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Character operations
    void SelectCharacter(int32_t characterId);
    void CreateCharacter(const char* name, int32_t classId);
    void DeleteCharacter(int32_t characterId);

    // Character properties
    int32_t GetSelectedCharacterId() const;
    const char* GetCharacterName(int32_t characterId) const;
    size_t GetCharacterCount() const;

    // Selection state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    struct Character {
        int32_t id;
        std::string name;
        int32_t classId;
    };

    bool m_initialized;
    bool m_visible;
    int32_t m_selectedCharacterId;
    std::vector<Character> m_characters;
};
