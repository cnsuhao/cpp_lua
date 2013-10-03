/*
1，开放给lua的函数中，如果参数或者返回值是字符串，则尽量使用const char*，不要使用std::string，
   使用std::string会有对象的构造析构成本。
2，对于从lua环境中返回出来的字符串，如果要保存的话，一定要自己分配内存空间，把字符串拷贝下来。
3，如果把一个对象开放到lua环境中，则该对象的析构函数也要开放到lua环境中，lua做GC操作时，如果
   找不到析构函数，则使用free操作释放内存，造成未知bug。
*/
#include "LuaExportSample.h"

namespace LuaExport
{
	void Script_GetNumber(int& nFirst, int& nSecond)
	{
		nFirst = 10;
		nSecond = 20;
	}
}
