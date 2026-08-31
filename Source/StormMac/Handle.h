#pragma once


#include <cstdint>
#include "Engine/Source/Agile/CHandleObject.h"

typedef void *HANDLE;

//#define DECLARE_HANDLE(name) \
//    struct name##__;         \
//    typedef struct name##__* name


struct HOBJECT__;
typedef struct HOBJECT__ *HOBJECT;

HOBJECT HandleCreate(CHandleObject *ptr);

void HandleClose(HOBJECT handle);

CHandleObject *HandleDereference(HOBJECT handle);

HOBJECT HandleDuplicate(HOBJECT handle);


