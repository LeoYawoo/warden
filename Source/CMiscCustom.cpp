#include "CMiscCustom.h"

// Reverse engineered from Warcraft III binary

CMiscCustom::CMiscCustom() : m_initialized(false), m_customValue(0) {}
CMiscCustom::~CMiscCustom() { Shutdown(); }

bool CMiscCustom::Initialize() {
    m_initialized = true;
    return true;
}

void CMiscCustom::Shutdown() {
    m_initialized = false;
}

bool CMiscCustom::IsInitialized() const { return m_initialized; }

const char* CMiscCustom::GetCustomName() const { return m_customName.c_str(); }
void CMiscCustom::SetCustomName(const char* name) { m_customName = name ? name : ""; }

int32_t CMiscCustom::GetCustomValue() const { return m_customValue; }
void CMiscCustom::SetCustomValue(int32_t value) { m_customValue = value; }
