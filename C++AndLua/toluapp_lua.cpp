/*
** Lua binding: toluapp
** Generated automatically by tolua++-1.0.92 on 10/03/13 21:55:06.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_toluapp_open (lua_State* tolua_S);

#include "LuaExportSample.h"
using namespace LuaExport;

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: Script_GetNumber */
#ifndef TOLUA_DISABLE_tolua_toluapp_Script_GetNumber00
static int tolua_toluapp_Script_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nFirst = ((int)  tolua_tonumber(tolua_S,1,0));
  int nSecond = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Script_GetNumber(nFirst,nSecond);
   tolua_pushnumber(tolua_S,(lua_Number)nFirst);
   tolua_pushnumber(tolua_S,(lua_Number)nSecond);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Script_GetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_toluapp_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,"Script_GetNumber",tolua_toluapp_Script_GetNumber00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_toluapp (lua_State* tolua_S) {
 return tolua_toluapp_open(tolua_S);
};
#endif

