#pragma once

#include <iostream>
#include "lobject.h"
#include "lstate.h"

const TValue luaO_nilobject_ = { NILCONSTANT };

/* value at a non-valid index */
#define NONVALIDVALUE        cast(TValue *, luaO_nilobject)
/* test for pseudo index */
#define ispseudo(i)        ((i) <= LUA_REGISTRYINDEX)

static TValue* index2addr(lua_State* L, int idx) {
	CallInfo* ci = L->ci;
	if (idx > 0) {
		TValue* o = ci->func + idx;
		api_check(L, idx <= ci->top - (ci->func + 1), "unacceptable index");
		if (o >= L->top) return NONVALIDVALUE;
		else return o;
	}
	else if (!ispseudo(idx)) {  /* negative index */
		api_check(L, idx != 0 && -idx <= L->top - (ci->func + 1), "invalid index");
		return L->top + idx;
	}
	else if (idx == LUA_REGISTRYINDEX)
		return &G(L)->l_registry;
	else {  /* upvalues */
		idx = LUA_REGISTRYINDEX - idx;
		api_check(L, idx <= MAXUPVAL + 1, "upvalue index too large");
		if (ttislcf(ci->func))  /* light C function? */
			return NONVALIDVALUE;  /* it has no upvalues */
		else {
			CClosure* func = clCvalue(ci->func);
			return (idx <= func->nupvalues) ? &func->upvalue[idx - 1] : NONVALIDVALUE;
		}
	}
}



/// <summary>
/// 打印lua栈
/// </summary>
/// <param name="L"></param>
void DumpLuaStack(lua_State* L)
{
	int ad = -1;
	int i = lua_gettop(L);
	printf("\n----------------  Stack Dump ----------------\n");
	while (i) {
		StkId o = index2addr(L, i);
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
			printf("%d[%d]:'%s'\n", i, ad, lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:
			printf("%d[%d]: %s\n", i, ad, lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			printf("%d[%d]: %g\n", i, ad, lua_tonumber(L, i));
			break;
		case LUA_TFUNCTION:
			if (ttislcf(o)) {
				printf("%d[%d]: c %p\n", i, ad, fvalue(o)); // lua_CFunction
			}
			else if (ttisCclosure(o))
			{
				printf("%d[%d]: c closure %p\n", i, ad, clCvalue(o)->f); // CClosure
			}
			else if (ttisLclosure(o))
			{
				Proto* pinfo = clLvalue(o)->p;
				printf("%d[%d]: lua closure %s[%d,%d]\n", i, ad, getstr(pinfo->source), pinfo->linedefined, pinfo->lastlinedefined);
			}
			break;
		case LUA_TTABLE:
			printf("%d[%d]: table:%p\n", i, ad, hvalue(o)); // 等价于printf("%d[%d]: table:%p\n", i, ad, lua_topointer(L, i));
			break;
		case LUA_TLIGHTUSERDATA:
			printf("%d[%d]: light userdata:%p\n", i, ad, pvalue(o));  // 等价于printf("%d[%d]: light userdata:%p\n", i, ad, lua_topointer(L, i));
			break;
		case LUA_TUSERDATA:
			printf("%d[%d]: full userdata:%p\n", i, ad, uvalue(o));
			break;
		case LUA_TTHREAD:
			printf("%d[%d]: thread:%p\n", i, ad, thvalue(o));  // 等价于printf("%d[%d]: thread:%p\n", i, ad, lua_topointer(L, i));
			break;
		default: printf("%d[%d]: %s\n", i, ad, lua_typename(L, t)); break;
		}
		i--; ad--;
	}
	printf("---------------------------------------------\n");
}






#include <cstring>
#include <string>
#include <vector>

extern "C"
{
#include "lua.h"
#include "lua.hpp"
#include "lualib.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lobject.h"
#include "lstate.h"
}
/* corresponding test */
#define isvalid(o)    ((o) != luaO_nilobject)

void GetLuaTValue(lua_State* L, StkId o, int t, int ad, int count, char* szOutput)
{
    int i = count + ad + 1;
    switch (t) {
    case LUA_TSTRING:
        sprintf_s(szOutput, 255, "%d[%d]: '%s'", i, ad, lua_tostring(L, i));
        break;
    case LUA_TBOOLEAN:
        sprintf_s(szOutput, 255, "%d[%d]: %s", i, ad, lua_toboolean(L, i) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        if (ttisinteger(o))
            sprintf_s(szOutput, 255, "%d[%d]: int %d", i, ad, (int)lua_tointeger(L, i));
        else
            sprintf_s(szOutput, 255, "%d[%d]: double %lf", i, ad, lua_tonumber(L, i));
        break;
    case LUA_TFUNCTION:
        if (ttislcf(o)) {
            sprintf_s(szOutput, 255, "%d[%d]: c 0x%p", i, ad, fvalue(o)); // lua_CFunction
        }
        else if (ttisCclosure(o))
        {
            sprintf_s(szOutput, 255, "%d[%d]: c closure 0x%p FucAdr:0x%p", i, ad, clCvalue(o), clCvalue(o)->f); // CClosure
        }
        else if (ttisLclosure(o))
        {
            Proto* pinfo = clLvalue(o)->p;
            sprintf_s(szOutput, 255, "%d[%d]: lua closure 0x%p %s[%d,%d]", i, ad, clLvalue(o), getstr(pinfo->source), pinfo->linedefined, pinfo->lastlinedefined);
        }
        break;
    case LUA_TTABLE:
        sprintf_s(szOutput, 255, "%d[%d]: table:0x%p", i, ad, hvalue(o));
        break;
    case LUA_TLIGHTUSERDATA:
        sprintf_s(szOutput, 255, "%d[%d]: light userdata:0x%p", i, ad, pvalue(o));
        break;
    case LUA_TUSERDATA:
        sprintf_s(szOutput, 255, "%d[%d]: full userdata:0x%p", i, ad, uvalue(o));
        break;
    case LUA_TTHREAD:
        sprintf_s(szOutput, 255, "%d[%d]: thread:0x%p", i, ad, thvalue(o));
        break;
    default: sprintf_s(szOutput, 255, "%d[%d]: %s", i, ad, lua_typename(L, t)); break;
    }
}

const char* VSDumpLuaStateTValue(lua_State* L, int n)
{
    static char s_szBuffer[256] = { 0 };
    memset(s_szBuffer, 0, 256);

    int ad = -1;
    int count = lua_gettop(L);
    int i = count;
    while (i) {
        if ((n < 0 ? ad : i) == n)
        {
            StkId o = index2addr(L, i);
            int t = (isvalid(o) ? ttnov(o) : LUA_TNONE);
            GetLuaTValue(L, o, t, ad, count, s_szBuffer);

            return s_szBuffer;
        }

        i--; ad--;
    }

    return "Lua Frame not found!";
}

std::vector<std::string> VSDumpLuaState(lua_State* L)
{
    std::vector<std::string> Msg;

    char szBuffer[256] = { 0 };
    memset(szBuffer, 0, 256);

    int ad = -1;
    int count = lua_gettop(L);
    int i = count;

    sprintf_s(szBuffer, 255, "----------------  Lua State Dump ----------------");
    Msg.push_back(szBuffer);
    while (i) {
        StkId o = index2addr(L, i);
        int t = (isvalid(o) ? ttnov(o) : LUA_TNONE);
        GetLuaTValue(L, o, t, ad, count, szBuffer);

        Msg.push_back(szBuffer);
        i--; ad--;
    }
    sprintf_s(szBuffer, 255, "---------------------------------------------");
    Msg.push_back(szBuffer);

    return Msg;
}

std::vector<std::string> VSDumpLuaCallStack(lua_State* L)
{
    std::vector<std::string> Msg;

    char szBuffer[256] = { 0 };
    memset(szBuffer, 0, 256);

    sprintf_s(szBuffer, 255, "----------------  Lua Call Stack Dump ----------------");
    Msg.push_back(szBuffer);

    CallInfo* curCi = L->ci;
    while (curCi != NULL)
    {
        StkId func = curCi->func;

        if (ttislcf(func)) {
            sprintf_s(szBuffer, 255, "++ CallStack: c 0x%p", fvalue(func)); // lua_CFunction
        }
        else if (ttisCclosure(func))
        {
            sprintf_s(szBuffer, 255, "++ CallStack: c closure 0x%p FucAdr:0x%p", clCvalue(func), clCvalue(func)->f); // CClosure
        }
        else if (ttisLclosure(func))
        {
            Proto* pinfo = clLvalue(func)->p;
#if 503 == LUA_VERSION_NUM
            int linenum = pinfo->lineinfo[(unsigned __int64)(curCi->u.l.savedpc) - (unsigned __int64)(pinfo->code) - 1];
#else             
            int linenum = luaG_getfuncline(pinfo, pcRel(curCi->u.l.savedpc, pinfo)); // lua 5.4
#endif
            sprintf_s(szBuffer, 255, "++ CallStack: lua closure 0x%p %s:%d", clLvalue(func), getstr(pinfo->source), linenum);
        }
        else
        {
            int funct = (isvalid(func) ? ttnov(func) : LUA_TNONE);
            sprintf_s(szBuffer, 255, "++ CallStack: %s", lua_typename(L, funct));
        }
        Msg.push_back(szBuffer);

        StkId locals = ((L->top < curCi->top) ? L->top : curCi->top) - 1;
        int ad = -1;
        int count = (int)(locals - func);
        while (locals > func)
        {
            StkId o = locals;
            int t = (isvalid(o) ? ttnov(o) : LUA_TNONE);
            GetLuaTValue(L, o, t, ad, count, szBuffer);
            Msg.push_back(szBuffer);
            --locals;
            --ad;
        }

        if (curCi == &(L->base_ci))
        {
            break;
        }

        curCi = curCi->previous;
    }


    sprintf_s(szBuffer, 255, "---------------------------------------------");
    Msg.push_back(szBuffer);

    return Msg;
}