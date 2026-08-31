#pragma once


#include <Windows.h>

typedef size_t Size;
typedef void *Handle;

FARPROC Carb_SystemFrameworkImport(const char *functionName);

Handle __cdecl NewHandle(Size byteCount);

Handle __cdecl NewHandleClear(Size byteCount);

Size __cdecl GetHandleSize(Handle h);

void __cdecl DisposeHandle(Handle h);


