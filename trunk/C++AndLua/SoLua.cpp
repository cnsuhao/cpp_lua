//-----------------------------------------------------------------------------
// SoLua
// (C) oil
// 2011-11-12
//-----------------------------------------------------------------------------
#include "SoLua.h"
#include <Windows.h>
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	bool SoLua::ExecuteFunc(lua_State* L, const char* pszFunc, const char* sig, ...)
	{
		if (L==0 || pszFunc==0 || sig==0)
		{
			return false;
		}
		//判断该函数是否存在。
		lua_getglobal(L, pszFunc);
		if (!lua_isfunction(L, -1))
		{
			//找不到这个函数。把压入的字符串弹出栈。
			lua_pop(L, 1);
			OutputDebugStringA("Can not find the function.");
			return false;
		}
		//执行lua函数。
		va_list vlist;
		va_start(vlist, sig);
		bool bResult = DoExecuteFunc(L, sig, vlist);
		va_end(vlist);
		//不管执行成功还是失败，把压入的函数名字弹出栈。
		lua_pop(L, 1);
		return bResult;
	}
	//-----------------------------------------------------------------------------
	bool SoLua::ExecuteTableFunc(lua_State* L, const char* pszTable, const char* pszFunc, const char* sig, ...)
	{
		if (L==0 || pszTable==0 || pszFunc==0 || sig==0)
		{
			return false;
		}
		//从lua环境中找到这个table。
		lua_getglobal(L, pszTable);
		if (!lua_istable(L, -1))
		{
			//找不到这个table。把压入的字符串弹出栈。
			lua_pop(L, 1);
			OutputDebugStringA("Can not find the table.");
			return false;
		}
		//从table中找到这个function。
		lua_getfield(L, -1, pszFunc);
		if (!lua_isfunction(L, -1))
		{
			//找不到这个function。弹出table和function两个元素。
			lua_pop(L, 2);
			OutputDebugStringA("Can not find the function.");
			return false;
		}
		//执行lua函数。
		va_list vlist;
		va_start(vlist, sig);
		bool bResult = DoExecuteFunc(L, sig, vlist);
		va_end(vlist);
		//不管执行成功还是失败，把压入的table名字和函数名字弹出栈。
		lua_pop(L, 2);
		return bResult;
	}
	//-----------------------------------------------------------------------------
	bool SoLua::ExecuteFile(lua_State* L, const char* pszLuaFile)
	{
		if (L==0 || pszLuaFile==0)
		{
			return false;
		}
		//从lua文件中获取文件内容。
		//可以是二进制内容也可以是文本内容。
		char* pFileBuff = 0;
		__int32 nFileSize = 0;
		if (!LoadFileToBuff(pszLuaFile, &pFileBuff, nFileSize))
		{
			return false;
		}
		//编译并执行。
		bool bResult = true;
		int nError = luaL_loadbuffer(L, pFileBuff, nFileSize, 0) || lua_pcall(L, 0, 0, 0);
		if (nError != 0)
		{
			//出错了。
			const char* pszErrorMsg = lua_tostring(L, -1);
			OutputDebugStringA(pszErrorMsg);
			//从栈中弹出错误信息。
			lua_pop(L, 1);
			bResult = false;
		}
		//释放缓存。
		if (pFileBuff)
		{
			free(pFileBuff);
		}
		return bResult;
	}
	//--------------------------------------------------------------------
	bool SoLua::ExecuteTrunk(lua_State* L, const char* pBuff, __int32 nBuffSize)
	{
		if (L==0 || pBuff==0)
		{
			return false;
		}
		if (nBuffSize <= 0)
		{
			nBuffSize = (__int32)strlen(pBuff);
		}
		bool bResult = true;
		int nError = luaL_loadbuffer(L, pBuff, nBuffSize, 0) || lua_pcall(L, 0, 0, 0);
		if (nError != 0)
		{
			//出错了。
			const char* pszErrorMsg = lua_tostring(L, -1);
			OutputDebugStringA(pszErrorMsg);
			//从栈中弹出错误信息。
			lua_pop(L, 1);
			bResult = false;
		}
		return bResult;
	}
	//--------------------------------------------------------------------
	bool SoLua::LoadFileToBuff(const char* pszFile, char** ppBuff, __int32& nBuffSize)
	{
		if (pszFile==0 || ppBuff==0)
		{
			return false;
		}
		//打开文件.
		FILE* fp = fopen(pszFile, "rb");
		if (fp == 0)
		{
			return false;
		}
		//计算文件大小.
		fseek(fp, 0, SEEK_END);
		nBuffSize = (__int32)ftell(fp);
		//分配Buff内存.
		*ppBuff = (char*)malloc(nBuffSize);
		if (*ppBuff == 0)
		{
			//申请内存失败。
			return false;
		}
		//填充Buff。
		fseek(fp, 0, SEEK_SET);
		const size_t sizeFileSize = (size_t)nBuffSize;
		size_t nActuallyRead = fread(*ppBuff, 1, sizeFileSize, fp);
		if (nActuallyRead != sizeFileSize)
		{
			free(*ppBuff);
			*ppBuff = 0;
			fclose(fp);
			return false;
		}
		//关闭文件。
		fclose(fp);
		return true;
	}
	//--------------------------------------------------------------------
	bool SoLua::DoExecuteFunc(lua_State* L, const char* sig, va_list& vlist)
	{
		//记录执行的结果，默认为成功。
		bool bResult = true;
		//记录函数调用之前栈内元素的个数。
		const int nStackElementCount_Before = lua_gettop(L);
		//参数个数。
		int narg = 0;
		//返回值个数。
		int nres = 0;
		//记录压入参数是否结束。
		bool bArgFinished = false;
		for (narg=0; *sig&&!bArgFinished; ++narg)
		{
			//检查栈中空间.
			luaL_checkstack(L, 1, "too many arguments");
			//鉴别参数类型.
			switch (*sig++)
			{
			case 'd': //double
				{
					lua_pushnumber(L, va_arg(vlist, double));
				}
				break;
			case 'i': //int
				{
					lua_pushinteger(L, va_arg(vlist, int));
				}
				break;
			case 's': //string
				{
					lua_pushstring(L, va_arg(vlist, char*));
				}
				break;
			case 'b': //bool
				{
					lua_pushboolean(L, va_arg(vlist, bool));
				}
				break;
			case '>': //参数结束
				{
					bArgFinished = true;
				}
				break;
			default:
				{
					//出错啦
					OutputDebugStringA("Invalid type.");
					bResult = false;
					goto finish;
				}
				break;
			}
		}
		if (bArgFinished)
		{
			//'>'符号导致narg多加了1，这里要减回去。
			--narg;
		}
		else
		{
			//没有出现'>'符号，说明没有返回值。
			bArgFinished = true;
		}
		//获取期望的返回值数量.
		nres = (int)strlen(sig);
		//调用函数.
		if (lua_pcall(L, narg, nres, 0) != 0)
		{
			//执行失败.
			const char* pszErrorMsg = lua_tostring(L, -1);
			OutputDebugStringA(pszErrorMsg);
			bResult = false;
			goto finish;
		}
		//第一个返回值的栈索引.
		nres = -nres;
		//遍历所有结果.
		while (*sig)
		{
			switch (*sig++)
			{
			case 'd': //double
				{
					if (lua_isnumber(L, nres))
					{
						*va_arg(vlist, double*) = lua_tonumber(L, nres);
					}
					else
					{
						bResult = false;
						goto finish;
					}
				}
				break;
			case 'i': //int
				{
					if (lua_isnumber(L, nres))
					{
						*va_arg(vlist, int*) = (int)lua_tointeger(L, nres);
					}
					else
					{
						bResult = false;
						goto finish;
					}
				}
				break;
			case 's': //string
				{
					if (lua_isstring(L, nres))
					{
						*va_arg(vlist, const char**) = lua_tostring(L, nres);
					}
					else
					{
						bResult = false;
						goto finish;
					}
				}
				break;
			case 'b': //bool
				{
					if (lua_isboolean(L, nres))
					{
						*va_arg(vlist, bool*) = (lua_toboolean(L, nres) != 0);
					}
					else
					{
						bResult = false;
						goto finish;
					}
				}
				break;
			default:
				{
					//出错啦
					OutputDebugStringA("Invalid type.");
					bResult = false;
					goto finish;
				}
				break;
			}
			++nres;
		}
		bResult = true;
finish:
		//检查栈状态,恢复到函数调用之前的栈状态.
		int nElementCountAfterExecute = lua_gettop(L);
		if (nStackElementCount_Before != nElementCountAfterExecute)
		{
			OutputDebugStringA("nStackElementCount_Before != nStackElementCount.");
			lua_settop(L, nStackElementCount_Before);
		}
		return bResult;
	}
}
//-----------------------------------------------------------------------------
