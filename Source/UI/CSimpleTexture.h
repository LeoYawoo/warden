#pragma once

#include "Engine/Source/Gx/Texture.h"
#include "UI/CSimpleRegion.h"
#include "UI/Types.h"
#include "Engine/Source/Tempest/CRect.h"
#include "Engine/Source/Tempest/C3Vector.h"
#include "Engine/Source/Gx/shader/CGxShader.h"

using namespace Tempest;

class CSimpleFrame;
enum TextureImageMode;
class CSimpleTexture : public CSimpleRegion {
public:
    // Static variables
    static CGxShader *s_imageModePixelShaders[];
    static uint16_t s_indices[];
    static int32_t s_metatable;
    static int32_t s_objectType;
    static EGxTexFilter s_textureFilterMode;

    // Static functions
    static void CreateScriptMetaTable();

    static CGxShader *GetImageModePixelShader(TextureImageMode mode);

    static int32_t GetObjectType();

    static void Init();

    static void RegisterScriptMethods(lua_State *L);

    // Member variables
    HTEXTURE m_texture = nullptr;
    EGxBlend m_alphaMode = GxBlend_Alpha;
    CGxShader *m_shader = s_imageModePixelShaders[0];
    C3Vector m_position[4];
    C2Vector m_texCoord[4];
    uint32_t m_nonBlocking: 1;
    uint32_t m_updateTexCoord: 1;
    uint32_t m_horizTile: 1;
    uint32_t m_vertTile: 1;

    // Virtual member functions
    virtual ~CSimpleTexture();

    virtual int32_t GetScriptMetaTable();

    virtual bool IsA(int32_t type);

    virtual void LoadXML(XMLNode *node, CStatus *status);

    virtual float GetWidth();

    virtual float GetHeight();

    virtual void Draw(CRenderBatch *batch);

    virtual void OnFrameSizeChanged(const CRect &rect);

    // Member functions
    CSimpleTexture(CSimpleFrame *frame, uint32_t drawlayer, int32_t show);

    void GetTexCoord(C2Vector *texCoord);

    void PostLoadXML(XMLNode *node, CStatus *status);

    void SetAlpha(float alpha);

    void SetBlendMode(EGxBlend blend);

    void SetPosition(const CRect &rect, C3Vector *position);

    void SetTexCoord(const CRect &texRect);

    void SetTexCoord(const C2Vector *texCoord);

    int32_t SetTexture(const char *fileName, bool wrapU, bool wrapV, EGxTexFilter filter, TextureImageMode mode);

    int32_t SetTexture(const CImVector &color);
};


