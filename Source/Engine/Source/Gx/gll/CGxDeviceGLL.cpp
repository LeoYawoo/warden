#include "CGxDeviceGLL.h"

// TODO: Reverse engineer from IDA

CGxDeviceGLL::CGxDeviceGLL()
    : CGxDevice() {
}

CGxDeviceGLL::~CGxDeviceGLL() = default;

void CGxDeviceGLL::ITexMarkAsUpdated(CGxTex *) {}
void CGxDeviceGLL::IRsSendToHw(EGxRenderState) {}
void *CGxDeviceGLL::DeviceWindow() { return nullptr; }
void CGxDeviceGLL::DeviceWM(EGxWM, uintptr_t, uintptr_t) {}
void CGxDeviceGLL::CapsWindowSize(CRect &) {}
void CGxDeviceGLL::CapsWindowSizeInScreenCoords(CRect &) {}
void CGxDeviceGLL::PoolSizeSet(CGxPool *, uint32_t) {}
void CGxDeviceGLL::IShaderCreate(CGxShader *) {}
int32_t CGxDeviceGLL::StereoEnabled() { return 0; }
