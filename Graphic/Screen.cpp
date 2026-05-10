#include "Screen.h"
#include "event/Event.h"
#include "Coordinate.h"
#include "Draw.h"
#include "Font.h"
#include "Transform.h"
#include "Common/TSExplicitList.h"
#include "Storm/Filesystem.h"
#include "Common/Region.h"
#include <storm/String.h>
#include "Game/CWorld.h"
#include "Terrain/TerrainRenderer.h"
#include "Graphic/Gx.h"
#include "Graphic/CCamera.h"
#include "Graphic/gll/GLDevice.h"
#include "glad/glad.h"
#include <cstdio>


int32_t Screen::s_captureScreen = 0;
float Screen::s_elapsedSec = 0.0f;
int32_t Screen::s_presentDisable = 0;
static HOBJECT s_stockObjects[SCRNSTOCKOBJECTS];
static float s_stockObjectHeights[SCRNSTOCKOBJECTS] = {0.01953125f, 0.01953125f};
static STORM_EXPLICIT_LIST(CILayer, zorderlink) s_zOrderList;

int32_t OnIdle(const EVENT_DATA_IDLE *data, void *a2) {
    Screen::s_elapsedSec = data->elapsedSec + Screen::s_elapsedSec;

    return 1;
}

int32_t OnPaint(const void *a1, void *a2) {
    static int paintCount = 0;
    paintCount++;
    FILE *plog = fopen("D:/dev_qt/w3/warden/build/debug_gll.log", "a");
    fprintf(plog, "[OnPaint] frame=%d\n", paintCount); fclose(plog);

    // TODO
    // if (!g_theGxDevicePtr || !g_theGxDevicePtr->CapsHasContext(-1) || !g_theGxDevicePtr->CapsIsWindowVisible(-1)) {
    //     // TODO
    //     // - sound engine logic
    //
    //     return 1;
    // }

    CSRgn rgn;
    SRgnCreate(&rgn.m_handle, 0);

    RECTF baseRect = {0.0f, 0.0f, 1.0f, 1.0f};
    SRgnCombineRectf(rgn.m_handle, &baseRect, nullptr, 2);

    // Walk the layer list backward (highest z-order to lowest) to establish visibility rects
    for (auto layer = s_zOrderList.Tail(); layer; layer = layer->zorderlink.Prev()) {
        SRgnGetBoundingRectf(rgn.m_handle, &layer->visible);

        layer->visible.left = (std::max)(layer->visible.left, layer->rect.left);
        layer->visible.bottom = (std::max)(layer->visible.bottom, layer->rect.bottom);
        layer->visible.right = (std::min)(layer->visible.right, layer->rect.right);
        layer->visible.top = (std::min)(layer->visible.top, layer->rect.top);

        if (!(layer->flags & 0x1)) {
            SRgnCombineRectf(rgn.m_handle, &layer->rect, nullptr, 4);
        }
    }

    SRgnDelete(rgn.m_handle);

    // Save viewport
    float minX, maxX, minY, maxY, minZ, maxZ;
    GxXformViewport(minX, maxX, minY, maxY, minZ, maxZ);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // STEP 1: Test if GLSL rendering works (core profile)
    // Simple vertex shader
    const char *vsSrc = R"(#version 330
        in vec2 aPos;
        in vec3 aColor;
        out vec3 vColor;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            vColor = aColor;
        })";
    const char *fsSrc = R"(#version 330
        in vec3 vColor;
        out vec4 fragColor;
        void main() {
            fragColor = vec4(vColor, 1.0);
        })";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    // Check compile/link status
    GLint ok;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    FILE *dlog = fopen("D:/dev_qt/w3/warden/build/debug_gll.log", "a");
    if (!ok) { char buf[512]; glGetShaderInfoLog(vs, 512, nullptr, buf); fprintf(dlog, "[OnPaint] VS compile error: %s\n", buf); }
    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[512]; glGetShaderInfoLog(fs, 512, nullptr, buf); fprintf(dlog, "[OnPaint] FS compile error: %s\n", buf); }
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    fprintf(dlog, "[OnPaint] GLSL program: link=%d err=%d\n", ok, (int)glGetError());

    // Draw triangle using VAO + VBO
    float verts[] = {
        -0.8f, -0.8f,  1,0,0,
         0.8f, -0.8f,  0,1,0,
         0.0f,  0.8f,  0,0,1,
    };
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glUseProgram(prog);
    glBindVertexArray(vao);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);

    glFinish();

    // Dump GL state to diagnose why drawing doesn't produce visible pixels
    GLint vp[4]; glGetIntegerv(GL_VIEWPORT, vp);
    GLint scissor[4]; glGetIntegerv(GL_SCISSOR_BOX, scissor);
    GLboolean scissorTest; glGetBooleanv(GL_SCISSOR_TEST, &scissorTest);
    GLboolean colorMask[4]; glGetBooleanv(GL_COLOR_WRITEMASK, colorMask);
    GLboolean depthMask; glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
    GLboolean depthTest; glGetBooleanv(GL_DEPTH_TEST, &depthTest);
    GLboolean blend; glGetBooleanv(GL_BLEND, &blend);
    GLboolean cull; glGetBooleanv(GL_CULL_FACE, &cull);

    unsigned char px[4];
    glReadPixels(512, 384, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
    fprintf(dlog, "[OnPaint] GLSL triangle: err=%d pixel=(%d,%d,%d,%d)\n",
        (int)glGetError(), px[0], px[1], px[2], px[3]);
    GLint cullFaceMode; glGetIntegerv(GL_CULL_FACE_MODE, &cullFaceMode);
    GLint frontFace; glGetIntegerv(GL_FRONT_FACE, &frontFace);
    fprintf(dlog, "[OnPaint] State: viewport=(%d,%d,%d,%d) scissor=(%d,%d,%d,%d) scissorTest=%d\n",
        vp[0], vp[1], vp[2], vp[3], scissor[0], scissor[1], scissor[2], scissor[3], (int)scissorTest);
    fprintf(dlog, "[OnPaint] State: colorMask=(%d,%d,%d,%d) depthMask=%d depthTest=%d blend=%d cull=%d cullFace=0x%x frontFace=0x%x\n",
        (int)colorMask[0], (int)colorMask[1], (int)colorMask[2], (int)colorMask[3],
        (int)depthMask, (int)depthTest, (int)blend, (int)cull, (int)cullFaceMode, (int)frontFace);
    fflush(dlog); fclose(dlog);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);

#if 0  // Disable UI layer rendering for terrain debug
    // Walk the layer list forward (lowest z-order to highest) to paint visible layers
    for (auto layer = s_zOrderList.Head(); layer; layer = layer->zorderlink.Next()) {
        if (layer->visible.right > layer->visible.left && layer->visible.top > layer->visible.bottom) {
            if (layer->flags & 0x4) {
                GxXformSetViewport(
                        0.0f,
                        1.0f,
                        0.0f,
                        1.0f,
                        0.0f,
                        1.0f
                );
            } else {
                GxXformSetViewport(
                        layer->visible.left,
                        layer->visible.right,
                        layer->visible.bottom,
                        layer->visible.top,
                        0.0f,
                        1.0f
                );
            }

            if (layer->flags & 0x2) {
                C44Matrix identity;
                GxXformSetView(identity);

                C44Matrix orthoProj;
                GxuXformCreateOrtho(
                        layer->visible.left,
                        layer->visible.right,
                        layer->visible.bottom,
                        layer->visible.top,
                        0.0f,
                        500.0f,
                        orthoProj
                );
                GxXformSetProjection(orthoProj);
            }

            layer->paintfunc(
                    layer->param,
                    &layer->rect,
                    &layer->visible,
                    Screen::s_elapsedSec
            );
        }
    }
#endif  // Disable UI layer rendering for terrain debug

    // Restore viewport
    GxXformSetViewport(minX, maxX, minY, maxY, minZ, maxZ);

    GxuFontUpdate();

    if (!Screen::s_presentDisable) {
        if (Screen::s_captureScreen) {
            // TODO

            GxSub682A00();

            // TODO

            return 1;
        }

        GxSub682A00();
    }

    Screen::s_elapsedSec = 0.0f;

    return 1;
}

void ILayerInitialize() {
    EventRegister(EVENT_ID_IDLE, reinterpret_cast<EVENTHANDLERFUNC>(OnIdle));
    EventRegister(EVENT_ID_PAINT, &OnPaint);
}

void IStockInitialize() {
    GxuFontInitialize();

    char fontFile[STORM_MAX_PATH];
    OsBuildFontFilePath("FRIZQT__.TTF", fontFile, sizeof(fontFile));

    if (*fontFile) {
        ScrnSetStockFont(STOCK_SYSFONT, fontFile);
    } else {
        // TODO
        // SErrSetLastError(0x57u);
    }

    if (*fontFile) {
        ScrnSetStockFont(STOCK_PERFFONT, fontFile);
    } else {
        // TODO
        // SErrSetLastError(0x57u);
    }
}

void ScrnInitialize(int32_t a1) {
    ILayerInitialize();

    // TODO
    // consoleInitialized = a1;

    IStockInitialize();
}

void ScrnLayerCreate(const RECTF *rect, float zOrder, uint32_t flags, void *param,
                     void (*paintFunc)(void *, const RECTF *, const RECTF *, float), HLAYER *layerPtr) {
    static RECTF defaultrect = {0.0f, 0.0f, 1.0f, 1.0f};
    const RECTF *r = rect ? rect : &defaultrect;

    auto m = SMemAlloc(sizeof(CILayer), __FILE__, __LINE__, 0x0);
    auto layer = new(m) CILayer();

    layer->rect.left = r->left;
    layer->rect.bottom = r->bottom;
    layer->rect.right = r->right;
    layer->rect.top = r->top;

    layer->zorder = zOrder;
    layer->flags = flags;
    layer->param = param;
    layer->paintfunc = paintFunc;

    auto node = s_zOrderList.Head();

    while (node && zOrder < node->zorder) {
        node = node->zorderlink.Next();
    }

    s_zOrderList.LinkNode(layer, 1, node);

    *layerPtr = HandleCreate(layer);
}

void ScrnLayerSetRect(HLAYER layer, const RECTF *rect) {
    static_cast<CILayer *>(HandleDereference(layer))->rect = *rect;
}

void ScrnSetStockFont(SCRNSTOCK stockID, const char *fontTexturePath) {
    if (s_stockObjects[stockID]) {
        HandleClose(s_stockObjects[stockID]);
    }

    float fontHeight = NDCToDDCHeight(s_stockObjectHeights[stockID]);
    HTEXTFONT font = TextBlockGenerateFont(fontTexturePath, 0, fontHeight);
    s_stockObjects[stockID] = font;
}
