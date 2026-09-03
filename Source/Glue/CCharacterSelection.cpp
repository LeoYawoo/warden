#include "CCharacterSelection.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CCharacterSelection::CCharacterSelection()
    : m_initialized(false), m_visible(true), m_selectedCharacterId(-1) {
}

CCharacterSelection::~CCharacterSelection() { Shutdown(); }

bool CCharacterSelection::Initialize() {
    m_initialized = true;
    m_visible = true;
    return true;
}

void CCharacterSelection::Shutdown() {
    m_initialized = false;
    m_characters.clear();
}

bool CCharacterSelection::IsInitialized() const { return m_initialized; }

void CCharacterSelection::SelectCharacter(int32_t characterId) {
    m_selectedCharacterId = characterId;
}

void CCharacterSelection::CreateCharacter(const char* name, int32_t classId) {
    if (!name) return;
    Character char_;
    char_.id = static_cast<int32_t>(m_characters.size()) + 1;
    char_.name = name;
    char_.classId = classId;
    m_characters.push_back(char_);
}

void CCharacterSelection::DeleteCharacter(int32_t characterId) {
    m_characters.erase(
        std::remove_if(m_characters.begin(), m_characters.end(),
            [characterId](const Character& c) { return c.id == characterId; }),
        m_characters.end());
}

int32_t CCharacterSelection::GetSelectedCharacterId() const { return m_selectedCharacterId; }

const char* CCharacterSelection::GetCharacterName(int32_t characterId) const {
    for (const auto& c : m_characters) {
        if (c.id == characterId) return c.name.c_str();
    }
    return nullptr;
}

size_t CCharacterSelection::GetCharacterCount() const { return m_characters.size(); }

bool CCharacterSelection::IsVisible() const { return m_visible; }
void CCharacterSelection::SetVisible(bool visible) { m_visible = visible; }
