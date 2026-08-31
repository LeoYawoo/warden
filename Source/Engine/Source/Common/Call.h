#pragma once

void OsCallDestroy();

void OsCallInitialize(const char* threadName);

void* OsCallInitializeContext(const char* contextName);

void OsCallResetContext(void* contextDataPtr);

void OsCallSetContext(void* contextDataPtr);


