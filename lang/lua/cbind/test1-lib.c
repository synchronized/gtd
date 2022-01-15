#include "lua.h"
#include "lauxlib.h"

int c_add(lua_State* L)
{
  int a = lua_tonumber(L, -2);
  int b = lua_tonumber(L, -1);
  int c = a + b;
  lua_pushnumber(L, c);
  return 1;
}

int c_step(lua_State* L)
{
  int a = lua_tonumber(L, -1);
  int b = a + 1;
  lua_pushnumber(L, b);
  return 1;
}

static const luaL_Reg mylib[] =
  {
    {"c_add", c_add},
    {"c_step", c_step},
    {NULL, NULL}
  };

int luaopen_mylib(lua_State* L)
{
  luaL_newlib(L, mylib);
  //luaL_openlib(L, "mylib", mylib, 0);
  //lua_register(L, "mylib", luaopen_mylib);
  return 1;
}
