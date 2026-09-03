#include "CControlSet.h"
#include "CControl.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CControlSet::CControlSet() {}
CControlSet::~CControlSet() {}

const char* CControlSet::GetSetName() const { return m_setName.c_str(); }
void CControlSet::SetSetName(const char* name) { m_setName = name ? name : ""; }

void CControlSet::AddControl(CControl* control) {
    if (control) m_controls.push_back(control);
}

void CControlSet::RemoveControl(CControl* control) {
    auto it = std::find(m_controls.begin(), m_controls.end(), control);
    if (it != m_controls.end()) m_controls.erase(it);
}

size_t CControlSet::GetControlCount() const { return m_controls.size(); }

CControl* CControlSet::GetControl(size_t index) const {
    return (index < m_controls.size()) ? m_controls[index] : nullptr;
}

CControl* CControlSet::GetControlByName(const char* name) const {
    if (!name) return nullptr;
    for (auto* control : m_controls) {
        if (control->GetFrameName() == name) return control;
    }
    return nullptr;
}

void CControlSet::Clear() { m_controls.clear(); }
bool CControlSet::IsEmpty() const { return m_controls.empty(); }
