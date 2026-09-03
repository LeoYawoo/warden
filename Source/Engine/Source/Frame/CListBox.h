#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CListBox is a list box UI control

class CListBox : public CControl {
public:
    CListBox();
    virtual ~CListBox();

    // ListBox operations
    void AddItem(const char* item);
    void RemoveItem(int32_t index);
    void ClearItems();

    // ListBox properties
    size_t GetItemCount() const;
    const char* GetItem(int32_t index) const;
    int32_t GetSelectedIndex() const;
    void SetSelectedIndex(int32_t index);

    // ListBox state
    bool IsMultiSelect() const;
    void SetMultiSelect(bool multiSelect);

protected:
    std::vector<std::string> m_items;
    int32_t m_selectedIndex;
    bool m_multiSelect;
};
