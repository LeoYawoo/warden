#pragma once
// TODO: Reverse engineer from IDA

#include "../CGxDevice.h"

class CGxDeviceGLL : public CGxDevice {
public:
    CGxDeviceGLL();
    ~CGxDeviceGLL();

    // Pure virtual overrides (stubs)
    void ITexMarkAsUpdated(CGxTex *) override;
    void IRsSendToHw(EGxRenderState) override;
    void *DeviceWindow() override;
    void DeviceWM(EGxWM wm, uintptr_t param1, uintptr_t param2) override;
    void CapsWindowSize(CRect &) override;
    void CapsWindowSizeInScreenCoords(CRect &dst) override;
    void PoolSizeSet(CGxPool *, uint32_t) override;
    void IShaderCreate(CGxShader *) override;
    int32_t StereoEnabled() override;
};
