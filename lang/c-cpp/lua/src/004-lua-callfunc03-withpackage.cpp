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

/*

 */

int main() {
    const char *script_define = R"(
function mypow(x, y)
    print("call func mypow")
    return x ^ y
end
)";

const char *script_call = R"(
print(pkg.mypow(2, 8))
)";


/**
需要达到这种效果
{
    "_G" = {
        "pkg" = {
            mypow = function{...}
        }
    }
}
*/

    auto lState = luaL_newstate();
    luaL_openlibs(lState); //注入标准库到lua

    {
        auto rst = luaL_loadbuffer(lState, script_define, strlen(script_define), "hello");
        if (rst) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer failed err:%s\n", "unknow error");
            }
            return -1;
        }
        printLuaStack(lState);

        //set upvalue
        lua_getglobal(lState, "_G"); //chunk, _G(table)
        if (!lua_istable(lState, -1)) {
            printLuaStack(lState);
            printf("the global _G type is not table\n");
            return -1;
        }
        printLuaStack(lState);
        //定义 package => pkg
        lua_newtable(lState); //chunk, _G(table), pkg(table)
        lua_pushstring(lState, "pkg"); //chunk, _G(table), pkg(table), "pkg"(string)
        lua_pushvalue(lState, -2); //chunk, _G(table), pkg(table), "pkg"(string), pkg(table)
        lua_rawset(lState, -4); //chunk, _G(table), pkg(table)
        printLuaStack(lState);
        //chunk, _G(table), pkg(table)
        //setupvalue (pkg(table)) 到 chunk
        auto upvalueName = lua_setupvalue(lState, -3, 1); //chunk, pkg(table)
        if (strcmp(upvalueName, "_ENV") != 0) {
            printf("lua_setupvalue return value is not _ENV");
            return -1;
        }
        printf("upvalueName: %s\n", upvalueName);
        printLuaStack(lState);
        lua_pop(lState, 1); //chunk

        //call the chunk
        if (lua_pcall(lState, 0, 0, 0)) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer failed err:%s\n", "unknow error");
            }
            return -1;
        }

        rst = luaL_loadbuffer(lState, script_call, strlen(script_call), "hello_call");
        if (rst) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer script_call failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer script_call err:%s\n", "unknow error");
            }
            return -1;
        }
        printLuaStack(lState);

        //call the chunk
        if (lua_pcall(lState, 0, 0, 0)) {
            if (lua_isstring(lState, -1)) {
                printf("loadbuffer failed err:%s\n", lua_tostring(lState, -1));
            } else {
                printf("loadbuffer failed err:%s\n", "unknow error");
            }
            return -1;
        }

    }

    printLuaStack(lState);
    lua_close(lState);
    return 0;
}
