#pragma once

#include <cstdint>

// Graphics buffer types
enum EGxBufferType {
    GxBufferType_Vertex = 0,
    GxBufferType_Index = 1
};

// Vertex attribute types
enum EGxVertexAttrib {
    GxVA_Position = 0,
    GxVA_BlendWeight = 1,
    GxVA_BlendIndices = 2,
    GxVA_Normal = 3,
    GxVA_Color0 = 4,
    GxVA_Color1 = 5,
    GxVA_TexCoord0 = 6,
    GxVA_TexCoord1 = 7,
    GxVAs_Last = 8
};

// Vertex buffer formats
enum EGxVertexBufferFormat {
    GxVBF_P = 0,
    GxVBF_PN = 1,
    GxVBF_PNC = 2,
    GxVBF_PNT = 3,
    GxVBF_PNCT = 4,
    GxVBF_PNT2 = 5,
    GxVBF_PNCT2 = 6,
    GxVBF_PC = 7,
    GxVBF_PCT = 8,
    GxVBF_PCT2 = 9,
    GxVBF_PT = 10,
    GxVBF_PT2 = 11,
    GxVBF_PBNT2 = 12,
    GxVBF_PNC2T2 = 13,
    GxVertexBufferFormats_Last = 14
};

// Vertex attribute descriptor
struct CGxVertexAttrib {
    EGxVertexAttrib attrib;
    uint32_t type;
    uint32_t offset;
    uint32_t bufSize;
};
