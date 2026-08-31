#pragma once

#include "event/Types.h"
#include <cstdint>
#include "../Tempest/C2iVector.h"

using namespace Tempest;

#define OS_QUEUE_SIZE 32

class EvtContext;

namespace Input {
    extern int32_t s_buttonDown[16];
    extern uint32_t s_buttonState;
    extern C2iVector s_currentMouse;
    extern uint32_t s_mouseHoldButton;
    extern MOUSEMODE s_mouseMode;
    extern uint32_t s_osButtonState;
    extern OS_MOUSE_MODE s_osMouseMode;
    extern int32_t s_numlockState;
    extern int32_t s_simulatedRightButtonClick;
    extern uint32_t s_metaKeyState;
    extern int32_t s_queueHead;
    extern int32_t s_queueTail;
    extern int32_t s_windowFocused;
    extern int32_t s_savedMouseSpeed;
}

void CheckMouseModeState();

MOUSEBUTTON ConvertButtonNumberToMOUSEBUTTON(int32_t buttonNumber);

void ConvertPosition(int32_t clientx, int32_t clienty, float *x, float *y);

void EventSetMouseMode(MOUSEMODE mode, uint32_t holdButton);

uint32_t GenerateMouseFlags();

const char *GetButtonName(int32_t button);

void IEvtInputInitialize();

int32_t IEvtInputProcess(EvtContext *context, int32_t *shutdown);

void IEvtInputSetMouseMode(EvtContext *context, MOUSEMODE mode, uint32_t holdButton);

const char *KeyCodeToString(KEY key);

int32_t OsInputGet(OSINPUT *id, int32_t *param0, int32_t *param1, int32_t *param2, int32_t *param3);

void OsInputInitialize();

bool OsInputIsUsingCocoaEventLoop();

void OsInputPostEvent(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3);

void OsInputSetMouseMode(OS_MOUSE_MODE mode);

int32_t OsQueueGet(OSINPUT *id, int32_t *param0, int32_t *param1, int32_t *param2, int32_t *param3);

void OsQueuePut(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3);

void OsQueueSetParam(int32_t index, int32_t param);

int32_t OsWindowProc(void *window, uint32_t message, uintptr_t wparam, intptr_t lparam);


