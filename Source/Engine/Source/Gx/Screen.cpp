#include "Screen.h"
#include "event/Event.h"
#include "Coordinate.h"
#include "Draw.h"
#include "Font.h"
#include "Transform.h"
#include "Common/TSExplicitList.h"
#include "StormMac/Filesystem.h"
#include "Common/Region.h"
#include <storm/String.h>
#include "Game/CWorld.h"
#include "Terrain/CTerrain.h"
#include "../Gx/Gx.h"
#include "../Gx/CCamera.h"
#include "../Gx/gll/GLDevice.h"
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

    // Render terrain
    CTerrain *terrain = CWorld::GetTerrain();
    if (terrain && terrain->IsValid()) {
        CRect windowSize;
        GxCapsWindowSize(windowSize);
        float w = windowSize.maxX - windowSize.minX;
        float h = windowSize.maxY - windowSize.minY;
        if (w > 0 && h > 0) {
            CRect projRect = {0.0f, 0.0f, w, h};

            CCamera camera;
            // Position camera to look at the terrain center
            float cx = terrain->GetOriginX() + terrain->GetCellsPerRow() * terrain->GetCellSize() * 0.5f;
            float cy = terrain->GetOriginY() + terrain->GetCellsPerCol() * terrain->GetCellSize() * 0.5f;
            camera.m_position.Set(C3Vector(cx, cy - 200.0f, 300.0f));
            camera.m_target.Set(C3Vector(cx, cy, 0.0f));
            camera.m_distance.Set(1.0f);
            camera.m_fov.Set(1.2f);
            camera.m_zFar.Set(10000.0f);
            camera.m_zNear.Set(10.0f);
            camera.SetupWorldProjection(projRect, 0);

            terrain->Render();
        }
    }

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
