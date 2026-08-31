#pragma once

class CGxShader;

class CRenderBatch;

class CSimpleRender {
public:
    // Static variables
    static CGxShader *s_vertexShader[];

    // Static functions
    static void DrawBatch(CRenderBatch *batch);

    static void Init();
};

