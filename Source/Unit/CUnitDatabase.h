#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CUnitDatabase manages unit type data

class CUnitDatabase {
public:
    CUnitDatabase();
    ~CUnitDatabase();

    // Database operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Unit type operations
    bool RegisterUnitType(int32_t typeId, const char* typeName);
    bool UnregisterUnitType(int32_t typeId);
    bool HasUnitType(int32_t typeId) const;

    // Unit type queries
    const char* GetUnitTypeName(int32_t typeId) const;
    int32_t GetUnitTypeCount() const;

protected:
    bool m_initialized;
    std::unordered_map<int32_t, std::string> m_unitTypes;
};
