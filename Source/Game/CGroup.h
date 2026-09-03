#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CGroup manages unit groups

class CGroup {
public:
    CGroup();
    ~CGroup();

    // Group properties
    int32_t GetGroupId() const;
    void SetGroupId(int32_t id);

    // Group operations
    void AddUnit(CUnit* unit);
    void RemoveUnit(CUnit* unit);
    void Clear();

    // Group queries
    size_t GetUnitCount() const;
    CUnit* GetUnit(size_t index) const;
    CUnit* GetUnitById(int32_t unitId) const;
    bool ContainsUnit(CUnit* unit) const;

protected:
    int32_t m_groupId;
    std::vector<CUnit*> m_units;
};
