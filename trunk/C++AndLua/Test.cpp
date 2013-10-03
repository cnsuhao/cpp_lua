#include "SoLua.h"
using namespace GGUI;

void main()
{
	lua_State* L = lua_open();
	luaL_openlibs(L);
	SoLua::ExecuteFile(L, "add.lua");
	int nExeResult = 0;
	SoLua::ExecuteFunc(L, "add", "ii>i", 3, 4, &nExeResult);
	SoLua::ExecuteTableFunc(L, "adddd", "add", "ii>i", 3, 4, &nExeResult);
	lua_close(L);
}