#include <iostream>
#include <cstdlib>
#include <cstring>

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
    const char *script = R"(
function helloworld()
    print("helloworld")
end
)";

    auto lState = luaL_newstate();
    luaL_openlibs(lState); //注入标准库到lua

    {
        auto rst = luaL_loadbuffer(lState, script, strlen(script), "hello");
        if (rst) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer failed err:%s\n", "unknow error");
            }
            return -1;
        }

        if (lua_pcall(lState, 0, 0, 0)) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer failed err:%s\n", "unknow error");
            }
            return -1;
        }
        //找到helloworld函数的位置并且压到站顶
        lua_getglobal(lState, "helloworld");
        if (!lua_isfunction(lState, -1)) {
            printf("lua func helloworld not found or not function\n");
            return -1;
        }
        if (lua_pcall(lState, 0, 0, 0)) {
            if (lua_isstring(lState, -1)) {
                printf("call lua func helloworld failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("call lua func helloworld failed err:%s\n", "unkonw");
            }
            return -1;
        }
    }

    printLuaStack(lState);
    lua_close(lState);
    return 0;
}
