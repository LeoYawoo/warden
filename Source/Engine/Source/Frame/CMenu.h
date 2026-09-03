#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CMenu is a menu UI control

class CMenu : public CControl {
public:
    CMenu();
    virtual ~CMenu();

    // Menu operations
    void AddItem(const char* text, int32_t id);
    void RemoveItem(int32_t id);
    void ClearItems();

    // Menu properties
    size_t GetItemCount() const;
    const char* GetItemText(int32_t id) const;
    int32_t GetSelectedItemId() const;
    void SetSelectedItemId(int32_t id);

    // Menu state
    bool IsOpen() const;
    void SetOpen(bool open);

protected:
    struct MenuItem {
        std::string text;
        int32_t id;
    };

    std::vector<MenuItem> m_items;
    int32_t m_selectedItemId;
    bool m_open;
};
