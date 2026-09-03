#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CInfoPanelUnitDetail displays unit details

class CInfoPanelUnitDetail {
public:
    CInfoPanelUnitDetail();
    ~CInfoPanelUnitDetail();

    // Panel properties
    void SetUnit(CUnit* unit);
    CUnit* GetUnit() const;

    // Panel state
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Panel info
    const char* GetUnitName() const;
    int32_t GetUnitLevel() const;
    int32_t GetUnitHealth() const;
    int32_t GetUnitMaxHealth() const;

protected:
    CUnit* m_unit;
    bool m_visible;
};
