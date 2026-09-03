#include "CMultiboardWar3.h"

// Reverse engineered from Warcraft III binary

CMultiboardWar3::CMultiboardWar3()
    : m_multiboardId(0), m_rows(0), m_columns(0),
      m_visible(true), m_minimized(false) {
}

CMultiboardWar3::~CMultiboardWar3() {}

int32_t CMultiboardWar3::GetMultiboardId() const { return m_multiboardId; }
void CMultiboardWar3::SetMultiboardId(int32_t id) { m_multiboardId = id; }

int32_t CMultiboardWar3::GetRowCount() const { return m_rows; }
int32_t CMultiboardWar3::GetColumnCount() const { return m_columns; }

void CMultiboardWar3::SetDimensions(int32_t rows, int32_t columns) {
    m_rows = rows;
    m_columns = columns;
    m_items.resize(rows, std::vector<MultiboardItem>(columns));
}

void CMultiboardWar3::SetItemTitle(int32_t row, int32_t column, const char* title) {
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        m_items[row][column].title = title ? title : "";
    }
}

void CMultiboardWar3::SetItemValue(int32_t row, int32_t column, int32_t value) {
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        m_items[row][column].value = value;
    }
}

void CMultiboardWar3::SetItemIcon(int32_t row, int32_t column, const char* icon) {
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        m_items[row][column].icon = icon ? icon : "";
    }
}

void CMultiboardWar3::SetItemStyle(int32_t row, int32_t column, int32_t style) {
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        m_items[row][column].style = style;
    }
}

bool CMultiboardWar3::IsVisible() const { return m_visible; }
void CMultiboardWar3::SetVisible(bool visible) { m_visible = visible; }

bool CMultiboardWar3::IsMinimized() const { return m_minimized; }
void CMultiboardWar3::SetMinimized(bool minimized) { m_minimized = minimized; }
