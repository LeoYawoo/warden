#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CMultiboardWar3 manages multiboards

class CMultiboardWar3 {
public:
    CMultiboardWar3();
    ~CMultiboardWar3();

    // Multiboard properties
    int32_t GetMultiboardId() const;
    void SetMultiboardId(int32_t id);

    // Multiboard dimensions
    int32_t GetRowCount() const;
    int32_t GetColumnCount() const;
    void SetDimensions(int32_t rows, int32_t columns);

    // Multiboard operations
    void SetItemTitle(int32_t row, int32_t column, const char* title);
    void SetItemValue(int32_t row, int32_t column, int32_t value);
    void SetItemIcon(int32_t row, int32_t column, const char* icon);
    void SetItemStyle(int32_t row, int32_t column, int32_t style);

    // Multiboard state
    bool IsVisible() const;
    void SetVisible(bool visible);

    bool IsMinimized() const;
    void SetMinimized(bool minimized);

protected:
    int32_t m_multiboardId;
    int32_t m_rows;
    int32_t m_columns;
    bool m_visible;
    bool m_minimized;

    struct MultiboardItem {
        std::string title;
        int32_t value;
        std::string icon;
        int32_t style;
    };

    std::vector<std::vector<MultiboardItem>> m_items;
};
