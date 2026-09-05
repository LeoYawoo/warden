#include "CGxDeviceOpenGl.h"
#include <QOpenGLFunctions>

// Reverse engineered from Warcraft III binary
// Original: Engine/Source/Gx/CGxDeviceOpenGL/CGxDeviceOpenGl.cpp

CGxDeviceOpenGl::CGxDeviceOpenGl() {
    m_api = GxApi_OpenGl;
}

CGxDeviceOpenGl::~CGxDeviceOpenGl() {
}

void CGxDeviceOpenGl::SetWindowHandle(void *handle) {
    m_windowHandle = handle;
}

void CGxDeviceOpenGl::SetGLFunctions(QOpenGLFunctions *funcs) {
    m_glFuncs = funcs;
}

// --- Pure virtual overrides ---

void CGxDeviceOpenGl::ITexMarkAsUpdated(CGxTex * /*tex*/) {
    // TODO: Mark texture for re-upload to GPU
}

void CGxDeviceOpenGl::IRsSendToHw(EGxRenderState /*state*/) {
    // TODO: Send render state to OpenGL
}

void *CGxDeviceOpenGl::DeviceWindow() {
    return m_windowHandle;
}

void CGxDeviceOpenGl::DeviceWM(EGxWM /*wm*/, uintptr_t /*param1*/, uintptr_t /*param2*/) {
    // TODO: Handle window messages
}

void CGxDeviceOpenGl::CapsWindowSize(CRect & /*rect*/) {
    // TODO: Return window size from caps
}

void CGxDeviceOpenGl::CapsWindowSizeInScreenCoords(CRect & /*dst*/) {
    // TODO: Return window size in screen coordinates
}

void CGxDeviceOpenGl::PoolSizeSet(CGxPool * /*pool*/, uint32_t /*size*/) {
    // TODO: Set pool size
}

void CGxDeviceOpenGl::IShaderCreate(CGxShader * /*shader*/) {
    // TODO: Create OpenGL shader program
}

int32_t CGxDeviceOpenGl::StereoEnabled() {
    return 0;
}

// --- Draw ---

void CGxDeviceOpenGl::Draw(CGxBatch *batch, int32_t indexed) {
    if (!batch || !m_glFuncs) return;

    if (indexed) {
        m_glFuncs->glDrawElements(
            static_cast<GLenum>(batch->m_primType),
            static_cast<GLsizei>(batch->m_count),
            GL_UNSIGNED_SHORT,
            reinterpret_cast<const void*>(static_cast<uintptr_t>(batch->m_minIndex * sizeof(uint16_t)))
        );
    } else {
        m_glFuncs->glDrawArrays(
            static_cast<GLenum>(batch->m_primType),
            static_cast<GLint>(batch->m_start),
            static_cast<GLsizei>(batch->m_count)
        );
    }
}
