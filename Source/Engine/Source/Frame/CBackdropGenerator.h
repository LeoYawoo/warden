#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CBackdropGenerator generates backdrop textures

class CBackdropGenerator {
public:
    CBackdropGenerator();
    ~CBackdropGenerator();

    // Generator properties
    int32_t GetGeneratorId() const;
    void SetGeneratorId(int32_t id);

    // Generator operations
    bool Generate();
    void Clear();

    // Generator state
    bool IsGenerated() const;

protected:
    int32_t m_generatorId;
    bool m_generated;
};
