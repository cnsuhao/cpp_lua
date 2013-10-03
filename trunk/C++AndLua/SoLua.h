//-----------------------------------------------------------------------------
// SoLua
// (C) oil
// 2011-11-12
//-----------------------------------------------------------------------------
#ifndef _SoLua_h_
#define _SoLua_h_
//-----------------------------------------------------------------------------
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
//-----------------------------------------------------------------------------
namespace GGUI
{
	class SoLua
	{
	public:
		//执行一个全局的lua函数。
		static bool ExecuteFunc(lua_State* L, const char* pszFunc, const char* sig, ...);
		//执行一个table内的lua函数。
		static bool ExecuteTableFunc(lua_State* L, const char* pszTable, const char* pszFunc, const char* sig, ...);
		//载入并执行一个lua文件。
		static bool ExecuteFile(lua_State* L, const char* pszLuaFile);

	private:
		//从磁盘上打开指定的文件，把文件内容读取到指定的Buff内。
		//函数内部会为Buff分配内存，由外界负责删除Buff。
		static bool LoadFileToBuff(const char* pszFile, char** ppBuff, __int32& nBuffSize);
		//执行lua函数。调用本函数前，要保证lua函数已经处于栈顶位置。
		static bool DoExecuteFunc(lua_State* L, const char* sig, va_list& vlist);
	};
}
//-----------------------------------------------------------------------------
#endif //_SoLua_h_
//-----------------------------------------------------------------------------
