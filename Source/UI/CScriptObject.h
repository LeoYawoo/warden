#pragma once

#include "UI/FrameScript_Object.h"
#include "Common/RCString.h"
#include "StormMac/xml/XMLNode.h"
#include <cstdint>


class CScriptObject : public FrameScript_Object {
public:
    // Static variables
    static int32_t s_objectType;
    static const char *s_objectTypeName;

    // Static functions
    static int32_t GetObjectType();

    static void RegisterScriptMethods(lua_State *L);

    static CScriptObject *GetScriptObjectByName(const char *name, int32_t type);

    // Member variables
    RCString m_name;

    // Virtual member functions
    virtual ~CScriptObject();

    virtual char *GetName();

    virtual bool IsA(int32_t type);

    virtual CScriptObject *GetScriptObjectParent() = 0;

    virtual bool IsA(const char *typeName);

    virtual const char *GetObjectTypeName();

    // Member functions
    void CreateName(const char *source, char *dest, uint32_t destsize);

    void PreLoadXML(XMLNode *node, CStatus *status);

    void SetName(const char *name);
};


