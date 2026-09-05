#pragma once

#include <cstdint>
#include <string>
#include "../Types.h"
#include "Common/TSLink.h"
#include "Common/TSGetLink.h"
#include "Common/Hashkey.h"

// Reverse engineered from Warcraft III binary
// CGxShader manages shader programs

class CGxShader {
public:
    CGxShader();
    ~CGxShader();

    // Shader properties
    EGxShTarget GetTarget() const;
    void SetTarget(EGxShTarget target);

    const char* GetName() const;
    void SetName(const char* name);

    // Shader state
    bool IsCompiled() const;
    void SetCompiled(bool compiled);
    bool Valid() const { return m_compiled; }

    // Load shader from file
    void Load(void* file);

    // Hash table link members (used by TSHashTable)
    TSLink<CGxShader> m_linktofull;
    TSLink<CGxShader> m_linktoslot;

    // Hash table key members
    uint32_t m_hashval;
    HASHKEY_STRI m_key;

    // Reference count
    int32_t refCount;

    // IDA offsets
    EGxShTarget target;
    int32_t loaded;
    int32_t int34;

protected:
    EGxShTarget m_target;
    std::string m_name;
    bool m_compiled;
};
