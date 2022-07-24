#include <iostream>
#include <cstdlib>

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"
#include "lauxlib.h"
}

void printLuaStack(lua_State* lua) {

    printf("========= content of stack from top to bottom: ===========\n");
    int stackSize = lua_gettop(lua);                    // 获得栈中元素个数
    printf("stacksize: %d\n", stackSize);

    for (int i=stackSize; i>0; --i) {
        printf("%d [%d]\t", i, -1 - (stackSize - i));

        int t = lua_type(lua, i);                       // 判断当前元素类型
        switch (t) {
        case LUA_TNUMBER:
            printf("%s: \t%.2f\n", lua_typename(lua, t), lua_tonumber(lua, i)); // 打印类型名称和值
            break;
        case LUA_TBOOLEAN:
            printf("%s: \t%d\n", lua_typename(lua, t), lua_toboolean(lua, i));
            break;
        case LUA_TSTRING:
            printf("%s: \t%s\n", lua_typename(lua, t), lua_tostring(lua, i));
            break;
        default:
            // LUA_TTABLE
            // LUA_TTHREAD
            // LUA_TFUNCTION
            // LUA_TLIGHTUSERDATA
            // LUA_TUSERDATA
            // LUA_TNIL
            printf("%s\n", lua_typename(lua, t)); // 不好打印的类型，暂时仅打印类型名称
            break;
        }
    }
}

int main() {
    auto lState = luaL_newstate();
    printLuaStack(lState);
    lua_close(lState);
    return 0;
}
