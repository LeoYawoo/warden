#pragma once
// Stub for Lua 5.1

#include <cstdint>
#include <cstdarg>

// Lua types
typedef struct lua_State lua_State;
typedef int (*lua_CFunction)(lua_State*);
typedef double lua_Number;
typedef ptrdiff_t lua_Integer;
typedef void *(*lua_Alloc)(void *ud, void *ptr, size_t osize, size_t nsize);

// Lua state
#define LUA_REGISTRYINDEX   (-10000)
#define LUA_ENVIRONINDEX    (-10001)
#define LUA_GLOBALSINDEX    (-10002)

// Lua status codes
#define LUA_OK              0
#define LUA_YIELD           1
#define LUA_ERRRUN          2
#define LUA_ERRSYNTAX       3
#define LUA_ERRMEM          4
#define LUA_ERRERR          5

// Lua type tags
#define LUA_TNONE           (-1)
#define LUA_TNIL            0
#define LUA_TBOOLEAN        1
#define LUA_TLIGHTUSERDATA  2
#define LUA_TNUMBER         3
#define LUA_TSTRING         4
#define LUA_TTABLE          5
#define LUA_TFUNCTION       6
#define LUA_TUSERDATA       7
#define LUA_TTHREAD         8

// Lua stack operations
inline int lua_gettop(lua_State*) { return 0; }
inline void lua_settop(lua_State*, int) {}
inline void lua_pushvalue(lua_State*, int) {}
inline void lua_remove(lua_State*, int) {}
inline void lua_insert(lua_State*, int) {}
inline void lua_replace(lua_State*, int) {}
inline void lua_rotate(lua_State*, int, int) {}
inline int lua_checkstack(lua_State*, int) { return 0; }

// Stack push operations
inline void lua_pushnil(lua_State*) {}
inline void lua_pushnumber(lua_State*, lua_Number) {}
inline void lua_pushinteger(lua_State*, lua_Integer) {}
inline void lua_pushlstring(lua_State*, const char*, size_t) {}
inline void lua_pushstring(lua_State*, const char*) {}
inline const char* lua_pushfstring(lua_State*, const char*, ...) { return ""; }
inline void lua_pushcclosure(lua_State*, lua_CFunction, int) {}
inline void lua_pushboolean(lua_State*, int) {}
inline void lua_pushlightuserdata(lua_State*, void*) {}

// Stack query operations
inline int lua_type(lua_State*, int) { return LUA_TNONE; }
inline const char* lua_typename(lua_State*, int) { return ""; }
inline lua_Number lua_tonumberx(lua_State*, int, int*) { return 0; }
inline lua_Integer lua_tointegerx(lua_State*, int, int*) { return 0; }
inline int lua_toboolean(lua_State*, int) { return 0; }
inline const char* lua_tolstring(lua_State*, int, size_t*) { return ""; }
inline lua_CFunction lua_tocfunction(lua_State*, int) { return nullptr; }
inline void* lua_touserdata(lua_State*, int) { return nullptr; }

// Macro versions
#define lua_tonumber(L,n)       lua_tonumberx(L,n,nullptr)
#define lua_tointeger(L,n)      lua_tointegerx(L,n,nullptr)
#define lua_tostring(L,n)       lua_tolstring(L,n,nullptr)
#define lua_to(L,n,type)        ((type*)lua_touserdata(L,n))

// Type checking
inline int lua_isnumber(lua_State*, int) { return 0; }
inline int lua_isstring(lua_State*, int) { return 0; }
inline int lua_iscfunction(lua_State*, int) { return 0; }
inline int lua_isuserdata(lua_State*, int) { return 0; }
inline int lua_isnil(lua_State*, int) { return 0; }
inline int lua_isnoneornil(lua_State*, int) { return 0; }

// Table operations
inline void lua_createtable(lua_State*, int, int) {}
inline void lua_newtable(lua_State*) {}
inline void* lua_newuserdata(lua_State*, size_t) { return nullptr; }
inline int lua_getmetatable(lua_State*, int) { return 0; }
inline void lua_setmetatable(lua_State*, int) {}
inline void lua_rawgeti(lua_State*, int, int) {}
inline void lua_rawseti(lua_State*, int, int) {}
inline void lua_setfield(lua_State*, int, const char*) {}
inline void lua_getfield(lua_State*, int, const char*) {}
inline void lua_settable(lua_State*, int) {}
inline void lua_gettable(lua_State*, int) {}
inline void lua_rawget(lua_State*, int) {}
inline void lua_rawset(lua_State*, int) {}
inline int lua_next(lua_State*, int) { return 0; }

// Function operations
inline int lua_pushglobaltable(lua_State*) { return 0; }
inline void lua_setglobal(lua_State*, const char*) {}
inline void lua_getglobal(lua_State*, const char*) {}
inline int lua_pcallk(lua_State*, int, int, int, lua_CFunction) { return 0; }

#define lua_pcall(L,n,r,f)     lua_pcallk(L,n,r,f,nullptr)
#define lua_call(L,n,r)        lua_pcallk(L,n,r,0,nullptr)

// Reference system
#define LUA_NOREF              (-2)
#define LUA_REFNIL             (-1)

// Registry
inline void* lua_newuserdatauv(lua_State*, size_t, int) { return nullptr; }

// Garbage collector
inline int lua_gc(lua_State*, int, int) { return 0; }
#define LUA_GCSTOP        0
#define LUA_GCRESTART      1
#define LUA_GCCOLLECT      2
#define LUA_GCCOUNT        3
#define LUA_GCCOUNTB       4
#define LUA_GCSTEP         5
#define LUA_GCSETPAUSE     6
#define LUA_GCSETSTEPMUL   7

// Error handling
inline int lua_error(lua_State*) { return 0; }
inline int lua_argerror(lua_State*, int, const char*) { return 0; }
inline int lua_typeerror(lua_State*, int, const char*) { return 0; }

// Debug interface
struct lua_Debug {
    int event;
    const char *name;
    const char *namewhat;
    const char *what;
    const char *source;
    int currentline;
    int nups;
    int linedefined;
    int lastlinedefined;
    char short_src[60];
    int i_ci;
};

inline int lua_getstack(lua_State*, int, lua_Debug*) { return 0; }
inline int lua_getinfo(lua_State*, const char*, lua_Debug*) { return 0; }
inline const char* lua_getlocal(lua_State*, const lua_Debug*, int) { return ""; }
inline const char* lua_setlocal(lua_State*, const lua_Debug*, int) { return ""; }

// String concatenation
inline void lua_concat(lua_State*, int) {}

// State creation
inline lua_State* lua_newstate(lua_Alloc, void*) { return nullptr; }

// Bit library opener (not in lualib.h)
inline int luaopen_bit(lua_State*) { return 0; }
