#include "CBackdropGenerator.h"

// Reverse engineered from Warcraft III binary

CBackdropGenerator::CBackdropGenerator() : m_generatorId(0), m_generated(false) {}
CBackdropGenerator::~CBackdropGenerator() {}

int32_t CBackdropGenerator::GetGeneratorId() const { return m_generatorId; }
void CBackdropGenerator::SetGeneratorId(int32_t id) { m_generatorId = id; }

bool CBackdropGenerator::Generate() {
    m_generated = true;
    return true;
}

void CBackdropGenerator::Clear() {
    m_generated = false;
}

bool CBackdropGenerator::IsGenerated() const { return m_generated; }
