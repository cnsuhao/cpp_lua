#include "SoLua.h"
using namespace GGUI;
extern int  tolua_toluapp_open (lua_State* tolua_S);

void main()
{
	lua_State* L = lua_open();
	luaL_openlibs(L);
	tolua_toluapp_open(L);
	/* 运行LUA脚本 */
	luaL_dofile(L, "test.lua");

	SoLua::ExecuteFile(L, "add.lua");
	int nExeResult = 0;
	SoLua::ExecuteFunc(L, "add", "ii>i", 3, 4, &nExeResult);
	SoLua::ExecuteTableFunc(L, "adddd", "add", "ii>i", 3, 4, &nExeResult);

	SoLua::ExecuteTrunk(L, "print(\"oil\")", 0);

	lua_close(L);
}