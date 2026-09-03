#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class CControl;

// Reverse engineered from Warcraft III binary
// CControlSet manages a set of controls

class CControlSet {
public:
    CControlSet();
    ~CControlSet();

    // Control set properties
    const char* GetSetName() const;
    void SetSetName(const char* name);

    // Control operations
    void AddControl(CControl* control);
    void RemoveControl(CControl* control);
    size_t GetControlCount() const;
    CControl* GetControl(size_t index) const;
    CControl* GetControlByName(const char* name) const;

    // Control set operations
    void Clear();
    bool IsEmpty() const;

protected:
    std::string m_setName;
    std::vector<CControl*> m_controls;
};
