#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void init_lua(lua_State* L)
{
  luaL_openlibs(L);
  luaopen_base(L);
  luaopen_table(L);
  luaopen_string(L);
  luaopen_math(L);
}


int main()
{
  lua_State* L = luaL_newstate();
  init_lua(L);

  if( luaL_loadfile(L, "test1.lua") != 0)
    {
      printf("fail to load\n");
      return -1;
    }

  //everything in lua is variable(including functions), so we need to init them.
  if( lua_pcall(L, 0, 0, 0))
    {
      printf("fail to run lua:%s\n", lua_tostring(L, -1));
      return -2;
    }

  //luaL_requiref(L, "mylib", luaopen_mylib, 0);

  //c call lua
  lua_getglobal(L, "l_ff");
  lua_pushnumber(L, 2);
  lua_pushnumber(L, 3);
  if( lua_pcall(L, 2, 1, 0) != 0)
    {
      printf("fail to call func: %s\n", lua_tostring(L, -1));
      return -3;
    }

  int res = lua_tonumber(L, -1);
  lua_pop(L, 1);
  printf("in c: %d\n", res);
  lua_close(L);
  return 0;
}
