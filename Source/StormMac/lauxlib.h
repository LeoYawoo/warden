#pragma once
// Stub for Lua auxiliary library

#include "lua.h"

#define LUA_COMPAT_ALL

inline int luaL_newmetatable(lua_State*, const char*) { return 0; }
inline void* luaL_checkudata(lua_State*, int, const char*) { return nullptr; }
inline void luaL_getmetatable(lua_State*, const char*) {}
inline int luaL_error(lua_State*, const char*, ...) { return 0; }
inline const char* luaL_checklstring(lua_State*, int, size_t*) { return ""; }
inline lua_Number luaL_checknumber(lua_State*, int) { return 0; }
inline lua_Integer luaL_checkinteger(lua_State*, int) { return 0; }
inline const char* luaL_optlstring(lua_State*, int, const char*, size_t*) { return ""; }
inline lua_Number luaL_optnumber(lua_State*, int, lua_Number def) { return def; }
inline lua_Integer luaL_optinteger(lua_State*, int, lua_Integer def) { return def; }
inline int luaL_typerror(lua_State*, int, const char*) { return 0; }
inline int luaL_argerror(lua_State*, int, const char*) { return 0; }
inline int luaL_ref(lua_State*, int) { return 0; }
inline void luaL_unref(lua_State*, int, int) {}
inline int luaL_loadbuffer(lua_State*, const char*, size_t, const char*) { return 0; }
inline int luaL_loadfile(lua_State*, const char*) { return 0; }
inline void luaL_openlibs(lua_State*) {}
inline int luaL_dostring(lua_State*, const char*) { return 0; }
inline void luaL_setfuncs(lua_State*, const void*, int) {}

#define luaL_register(L,n,l)    luaL_setfuncs(L,l,0)
#define luaL_checkstring(L,n)   luaL_checklstring(L,n,nullptr)
#define luaL_checkinteger(L,n)  luaL_checkinteger(L,n)
#define luaL_optstring(L,n,d)   luaL_optlstring(L,n,d,nullptr)

struct luaL_Reg {
    const char* name;
    lua_CFunction func;
};
