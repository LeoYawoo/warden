#pragma once
// Stub for Lua standard libraries

#include "lua.h"

// Standard library names
#define LUA_BASELIBNAME    "_G"
#define LUA_TABLIBNAME     "table"
#define LUA_IOLIBNAME      "io"
#define LUA_OSLIBNAME      "os"
#define LUA_STRLIBNAME     "string"
#define LUA_MATHLIBNAME    "math"
#define LUA_DBLIBNAME      "debug"
#define LUA_LOADLIBNAME    "package"

// Standard library open functions
inline int luaopen_base(lua_State*) { return 0; }
inline int luaopen_table(lua_State*) { return 0; }
inline int luaopen_io(lua_State*) { return 0; }
inline int luaopen_os(lua_State*) { return 0; }
inline int luaopen_string(lua_State*) { return 0; }
inline int luaopen_math(lua_State*) { return 0; }
inline int luaopen_debug(lua_State*) { return 0; }
inline int luaopen_package(lua_State*) { return 0; }
