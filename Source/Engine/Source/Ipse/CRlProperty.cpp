#include "CRlProperty.h"

// Reverse engineered from Warcraft III binary

namespace NIpse {

CRlProperty::CRlProperty() : m_propertyId(0), m_value(0.0f), m_valid(true) {}

CRlProperty::~CRlProperty() {}

int32_t CRlProperty::GetPropertyId() const { return m_propertyId; }
void CRlProperty::SetPropertyId(int32_t id) { m_propertyId = id; }

const char* CRlProperty::GetPropertyName() const { return m_propertyName.c_str(); }
void CRlProperty::SetPropertyName(const char* name) { m_propertyName = name ? name : ""; }

float CRlProperty::GetValue() const { return m_value; }
void CRlProperty::SetValue(float value) { m_value = value; }

bool CRlProperty::IsValid() const { return m_valid; }
void CRlProperty::SetValid(bool valid) { m_valid = valid; }

} // namespace NIpse
