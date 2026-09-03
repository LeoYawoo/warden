#include "CListBox.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CListBox::CListBox() : m_selectedIndex(-1), m_multiSelect(false) { m_controlType = "ListBox"; }
CListBox::~CListBox() {}

void CListBox::AddItem(const char* item) {
    if (item) m_items.push_back(item);
}

void CListBox::RemoveItem(int32_t index) {
    if (index >= 0 && static_cast<size_t>(index) < m_items.size()) {
        m_items.erase(m_items.begin() + index);
        if (m_selectedIndex >= static_cast<int32_t>(m_items.size())) {
            m_selectedIndex = static_cast<int32_t>(m_items.size()) - 1;
        }
    }
}

void CListBox::ClearItems() {
    m_items.clear();
    m_selectedIndex = -1;
}

size_t CListBox::GetItemCount() const { return m_items.size(); }

const char* CListBox::GetItem(int32_t index) const {
    if (index >= 0 && static_cast<size_t>(index) < m_items.size()) {
        return m_items[index].c_str();
    }
    return nullptr;
}

int32_t CListBox::GetSelectedIndex() const { return m_selectedIndex; }
void CListBox::SetSelectedIndex(int32_t index) { m_selectedIndex = index; }

bool CListBox::IsMultiSelect() const { return m_multiSelect; }
void CListBox::SetMultiSelect(bool multiSelect) { m_multiSelect = multiSelect; }
