#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

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

int aries_pow(lua_State* lState) {
    auto paramNum = lua_gettop(lState);
    if (paramNum != 2) {
        lua_pushstring(lState, "aries.pow must 2 params");
        lua_error(lState);
    }
    if (!lua_isnumber(lState, 1) || !lua_isnumber(lState, 2)) {
        lua_pushstring(lState, "aries.pow params must type float");
        lua_error(lState);
    }
    auto x = lua_tonumber(lState, 1);
    auto y = lua_tonumber(lState, 2);
    auto rst = pow(x, y);
    lua_pushnumber(lState, rst);
    return 1;
}

const char* script_call = R"(
local x = aries_pow(2, 8)
print(x)
)";

int main() {
    auto lState = luaL_newstate();
    luaL_openlibs(lState);
    lua_getglobal(lState, "_G"); //_G
    if (!lua_istable(lState, -1)) {
        printf("the global _G type is not table\n");
        return -1;
    }
    printLuaStack(lState);

    lua_pushstring(lState, "aries_pow"); //_G, "aries_pow"(string)
    lua_pushcclosure(lState, aries_pow, 0); //_G, "aries_pow"(string), aries_pow(cfunc)
    lua_rawset(lState, -3); //_G

    //_G, aries(table), script_call(chunk)
    auto rst = luaL_loadbuffer(lState, script_call, strlen(script_call), "script_call");
    if (rst) {
        if (lua_isstring(lState, -1)) {
            printf("loadbuffer script_call failed err: %s\n", lua_tostring(lState, -1));
        } else {
            printf("loadbuffer script_call failed err: %s\n", "unknow error");
        }
        return -1;
    }
    printLuaStack(lState);


    rst = lua_pcall(lState, 0, 0, 0);
    if (rst) {
        if (lua_isstring(lState, -1)) {
            printf("pcall script_call failed err: %s\n", lua_tostring(lState, -1));
        } else {
            printf("pcall script_call failed err: %s\n", "unknow error");
        }
        return -1;
    }

    lua_close(lState);
    return 0;
}
