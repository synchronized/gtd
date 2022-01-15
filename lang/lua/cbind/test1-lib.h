#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int c_add(lua_State* L);

int c_step(lua_State* L);

LUALIB_API int luaopen_mylib(lua_State* L);
