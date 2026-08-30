#include <gtest/gtest.h>
#include "Event/Types.h"

TEST(EventTypesTest, EVENTIDValues) {
    EXPECT_EQ(EVENT_ID_0, 0);
    EXPECT_EQ(EVENT_ID_CHAR, 1);
    EXPECT_EQ(EVENT_ID_FOCUS, 2);
    EXPECT_EQ(EVENT_ID_DESTROY, 4);
    EXPECT_EQ(EVENT_ID_IDLE, 6);
    EXPECT_EQ(EVENT_ID_KEYDOWN, 9);
    EXPECT_EQ(EVENT_ID_KEYUP, 10);
    EXPECT_EQ(EVENT_ID_MOUSEDOWN, 12);
    EXPECT_EQ(EVENT_ID_MOUSEMOVE, 13);
    EXPECT_EQ(EVENT_ID_MOUSEUP, 15);
    EXPECT_EQ(EVENT_ID_PAINT, 23);
    EXPECT_EQ(EVENTIDS, 36);
}

TEST(EventTypesTest, KEYValues) {
    EXPECT_EQ(KEY_NONE, 0xFFFFFFFF);
    EXPECT_EQ(KEY_LSHIFT, 0x0);
    EXPECT_EQ(KEY_SPACE, 0x20);
    EXPECT_EQ(KEY_0, 0x30);
    EXPECT_EQ(KEY_9, 0x39);
    EXPECT_EQ(KEY_A, 0x41);
    EXPECT_EQ(KEY_Z, 0x5A);
    EXPECT_EQ(KEY_ESCAPE, 0x200);
    EXPECT_EQ(KEY_ENTER, 0x201);
    EXPECT_EQ(KEY_F1, 0x300);
    EXPECT_EQ(KEY_F12, 0x30B);
    EXPECT_EQ(KEY_LAST, 0x313);
}

TEST(EventTypesTest, MOUSEBUTTONValues) {
    EXPECT_EQ(MOUSE_BUTTON_NONE, 0x0);
    EXPECT_EQ(MOUSE_BUTTON_LEFT, 0x1);
    EXPECT_EQ(MOUSE_BUTTON_MIDDLE, 0x2);
    EXPECT_EQ(MOUSE_BUTTON_RIGHT, 0x4);
    EXPECT_EQ(MOUSE_BUTTON_ALL, 0xFFFFFFFF);
}

TEST(EventTypesTest, MOUSEMODEValues) {
    EXPECT_EQ(MOUSE_MODE_NORMAL, 0x0);
    EXPECT_EQ(MOUSE_MODE_RELATIVE, 0x1);
    EXPECT_EQ(MOUSE_MODES, 0x2);
}

TEST(EventTypesTest, OSINPUTValues) {
    EXPECT_EQ(OS_INPUT_CAPTURE_CHANGED, 0);
    EXPECT_EQ(OS_INPUT_CHAR, 1);
    EXPECT_EQ(OS_INPUT_KEY_DOWN, 7);
    EXPECT_EQ(OS_INPUT_KEY_UP, 8);
    EXPECT_EQ(OS_INPUT_MOUSE_DOWN, 9);
    EXPECT_EQ(OS_INPUT_MOUSE_MOVE, 10);
    EXPECT_EQ(OS_INPUT_MOUSE_WHEEL, 11);
    EXPECT_EQ(OS_INPUT_SHUTDOWN, 19);
}

TEST(EventTypesTest, EventDataStructures) {
    // Test EVENT_DATA_CHAR
    EVENT_DATA_CHAR charData;
    charData.ch = 'A';
    charData.metaKeyState = 0;
    charData.repeat = 1;
    EXPECT_EQ(charData.ch, 'A');

    // Test EVENT_DATA_FOCUS
    EVENT_DATA_FOCUS focusData;
    focusData.focus = 1;
    EXPECT_EQ(focusData.focus, 1);

    // Test EVENT_DATA_IDLE
    EVENT_DATA_IDLE idleData;
    idleData.elapsedSec = 1.5f;
    idleData.time = 1000;
    EXPECT_FLOAT_EQ(idleData.elapsedSec, 1.5f);

    // Test EVENT_DATA_KEY
    EVENT_DATA_KEY keyData;
    keyData.key = KEY_A;
    keyData.metaKeyState = 0;
    keyData.repeat = 0;
    keyData.time = 1000;
    EXPECT_EQ(keyData.key, KEY_A);

    // Test EVENT_DATA_MOUSE
    EVENT_DATA_MOUSE mouseData;
    mouseData.mode = MOUSE_MODE_NORMAL;
    mouseData.button = MOUSE_BUTTON_LEFT;
    mouseData.buttonState = 1;
    mouseData.x = 100.0f;
    mouseData.y = 200.0f;
    EXPECT_FLOAT_EQ(mouseData.x, 100.0f);

    // Test EVENT_DATA_SIZE
    EVENT_DATA_SIZE sizeData;
    sizeData.w = 800;
    sizeData.h = 600;
    EXPECT_EQ(sizeData.w, 800);
    EXPECT_EQ(sizeData.h, 600);
}

TEST(EventTypesTest, OSEVENTStruct) {
    OSEVENT osEvent;
    osEvent.id = OS_INPUT_KEY_DOWN;
    osEvent.param[0] = KEY_A;
    osEvent.param[1] = 0;
    osEvent.param[2] = 0;
    osEvent.param[3] = 0;

    EXPECT_EQ(osEvent.id, OS_INPUT_KEY_DOWN);
    EXPECT_EQ(osEvent.param[0], KEY_A);
}

TEST(EventTypesTest, KeyInRange) {
    // Test that key values are in expected ranges
    EXPECT_GE(KEY_A, 0x41);
    EXPECT_LE(KEY_Z, 0x5A);

    EXPECT_GE(KEY_F1, 0x300);
    EXPECT_LE(KEY_F12, 0x30B);

    EXPECT_GE(KEY_NUMPAD0, 0x100);
    EXPECT_LE(KEY_NUMPAD9, 0x109);
}
