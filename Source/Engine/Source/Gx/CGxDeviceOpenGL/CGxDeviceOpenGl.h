#pragma once

// Reverse engineered from Warcraft III binary
// CGxDeviceOpenGl - Cross-platform OpenGL device implementation
// Original: Engine/Source/Gx/CGxDeviceOpenGL/CGxDeviceOpenGl.cpp

#include "../CGxDevice.h"

class QOpenGLFunctions;

class CGxDeviceOpenGl : public CGxDevice {
public:
    CGxDeviceOpenGl();
    ~CGxDeviceOpenGl();

    // CGxDevice pure virtual overrides
    void ITexMarkAsUpdated(CGxTex *tex) override;
    void IRsSendToHw(EGxRenderState state) override;
    void *DeviceWindow() override;
    void DeviceWM(EGxWM wm, uintptr_t param1, uintptr_t param2) override;
    void CapsWindowSize(CRect &rect) override;
    void CapsWindowSizeInScreenCoords(CRect &dst) override;
    void PoolSizeSet(CGxPool *pool, uint32_t size) override;
    void IShaderCreate(CGxShader *shader) override;
    int32_t StereoEnabled() override;

    // Draw
    void Draw(CGxBatch *batch, int32_t indexed) override;

    // GL context management
    void SetWindowHandle(void *handle);
    void SetGLFunctions(QOpenGLFunctions *funcs);

private:
    void *m_windowHandle = nullptr;
    QOpenGLFunctions *m_glFuncs = nullptr;
};
