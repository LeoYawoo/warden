#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CSelectionWar3 manages unit selection

class CSelectionWar3 {
public:
    CSelectionWar3();
    ~CSelectionWar3();

    // Selection operations
    void SelectUnit(CUnit* unit);
    void DeselectUnit(CUnit* unit);
    void ClearSelection();
    void SelectAll();

    // Selection queries
    size_t GetSelectionCount() const;
    CUnit* GetSelectedUnit(size_t index) const;
    bool IsUnitSelected(CUnit* unit) const;

    // Selection state
    bool IsMultiSelect() const;
    void SetMultiSelect(bool multiSelect);

protected:
    std::vector<CUnit*> m_selectedUnits;
    bool m_multiSelect;
};
