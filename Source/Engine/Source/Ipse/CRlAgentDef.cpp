#include "CRlAgentDef.h"

// Reverse engineered from Warcraft III binary

namespace NIpse {

CRlAgentDef::CRlAgentDef() : m_defId(0), m_valid(true) {}

CRlAgentDef::~CRlAgentDef() {}

int32_t CRlAgentDef::GetDefId() const { return m_defId; }
void CRlAgentDef::SetDefId(int32_t id) { m_defId = id; }

const char* CRlAgentDef::GetDefName() const { return m_defName.c_str(); }
void CRlAgentDef::SetDefName(const char* name) { m_defName = name ? name : ""; }

bool CRlAgentDef::IsValid() const { return m_valid; }
void CRlAgentDef::SetValid(bool valid) { m_valid = valid; }

void CRlAgentDef::Reset() {
    m_defId = 0;
    m_defName.clear();
    m_valid = true;
}

void CRlAgentDef::Clear() {
    m_defId = 0;
    m_defName.clear();
    m_valid = false;
}

} // namespace NIpse
