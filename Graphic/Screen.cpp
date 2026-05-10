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
    fprintf(stderr, "[Screen] OnPaint START frame=%d\n", paintCount); fflush(stderr);

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

    // Test clear to verify GL context works
    fprintf(stderr, "[Screen] glClear to blue...\n"); fflush(stderr);
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLenum clearErr = glGetError();
    fprintf(stderr, "[Screen] glClear done, err=%d\n", (int)clearErr); fflush(stderr);
    // Clear any accumulated GL errors before terrain
    while (glGetError() != GL_NO_ERROR) {}

    // Render terrain before UI layers
    TerrainRenderer *terrain = CWorld::GetTerrain();
    fprintf(stderr, "[Screen] TerrainRenderer=%p valid=%d\n", (void*)terrain, terrain ? terrain->IsValid() : 0); fflush(stderr);
    if (terrain && terrain->IsValid()) {
        CRect windowSize;
        GxCapsWindowSize(windowSize);
        float w = windowSize.maxX - windowSize.minX;
        float h = windowSize.maxY - windowSize.minY;
        fprintf(stderr, "[Screen] window size: %.0f x %.0f\n", w, h); fflush(stderr);
        if (w > 0 && h > 0) {
            CRect projRect = {0.0f, 0.0f, w, h};

            CCamera camera;
            camera.m_position.Set(C3Vector(150.0f, 150.0f, 100.0f));
            camera.m_target.Set(C3Vector(128.0f, 128.0f, 20.0f));
            camera.m_distance.Set(1.0f);
            camera.m_fov.Set(0.8f);
            camera.m_zFar.Set(2000.0f);
            camera.m_zNear.Set(1.0f);
            fprintf(stderr, "[Screen] Setting up camera...\n"); fflush(stderr);
            camera.SetupWorldProjection(projRect, 0);

            fprintf(stderr, "[Screen] Calling terrain->Render()...\n"); fflush(stderr);
            terrain->Render();
            fprintf(stderr, "[Screen] terrain->Render() done\n"); fflush(stderr);
        }
    }

    fprintf(stderr, "[Screen] Layer loop SKIPPED for testing, presentDisable=%d\n", Screen::s_presentDisable); fflush(stderr);

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

        fprintf(stderr, "[Screen] SKIPPING GxSub682A00 (Swap) for testing...\n"); fflush(stderr);
        glFlush();  // test: flush without Swap to isolate crash
        fprintf(stderr, "[Screen] glFlush done\n"); fflush(stderr);
    }

    Screen::s_elapsedSec = 0.0f;

    fprintf(stderr, "[Screen] OnPaint END\n"); fflush(stderr);
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
