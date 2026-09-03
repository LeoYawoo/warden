#include "CMenu.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CMenu::CMenu() : m_selectedItemId(-1), m_open(false) { m_controlType = "Menu"; }
CMenu::~CMenu() {}

void CMenu::AddItem(const char* text, int32_t id) {
    if (text) m_items.push_back({text, id});
}

void CMenu::RemoveItem(int32_t id) {
    m_items.erase(std::remove_if(m_items.begin(), m_items.end(),
        [id](const MenuItem& item) { return item.id == id; }), m_items.end());
}

void CMenu::ClearItems() { m_items.clear(); }

size_t CMenu::GetItemCount() const { return m_items.size(); }

const char* CMenu::GetItemText(int32_t id) const {
    for (const auto& item : m_items) {
        if (item.id == id) return item.text.c_str();
    }
    return nullptr;
}

int32_t CMenu::GetSelectedItemId() const { return m_selectedItemId; }
void CMenu::SetSelectedItemId(int32_t id) { m_selectedItemId = id; }

bool CMenu::IsOpen() const { return m_open; }
void CMenu::SetOpen(bool open) { m_open = open; }
