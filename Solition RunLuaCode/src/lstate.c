/*
** $Id: lstate.c,v 2.133.1.1 2017/04/19 17:39:34 roberto Exp $
** Global State
** See Copyright Notice in lua.h
*/

#define lstate_c
#define LUA_CORE

#include "lprefix.h"


#include <stddef.h>
#include <string.h>

#include "lua.h"

#include "lapi.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "llex.h"
#include "lmem.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"


#if !defined(LUAI_GCPAUSE)
#define LUAI_GCPAUSE	200  /* 200% */
#endif

#if !defined(LUAI_GCMUL)
#define LUAI_GCMUL	200 /* GC runs 'twice the speed' of memory allocation */
#endif


/*
** a macro to help the creation of a unique random seed when a state is
** created; the seed is used to randomize hashes.
*/
#if !defined(luai_makeseed)
#include <time.h>
#define luai_makeseed()		cast(unsigned int, time(NULL))
#endif



/*
** thread state + extra space
*/
typedef struct LX {
	lu_byte extra_[LUA_EXTRASPACE];
	lua_State l;
} LX;


/*
** Main thread combines a thread state and the global state
*/
typedef struct LG {
	LX l;
	global_State g;
} LG;



#define fromstate(L)	(cast(LX *, cast(lu_byte *, (L)) - offsetof(LX, l)))


/*
** Compute an initial seed as random as possible. Rely on Address Space
** Layout Randomization (if present) to increase randomness..
*/
#define addbuff(b,p,e) \
  { size_t t = cast(size_t, e); \
    memcpy(b + p, &t, sizeof(t)); p += sizeof(t); }

static unsigned int makeseed(lua_State* L) {
	char buff[4 * sizeof(size_t)];
	unsigned int h = luai_makeseed();
	int p = 0;
	addbuff(buff, p, L);  /* heap variable */
	addbuff(buff, p, &h);  /* local variable */
	addbuff(buff, p, luaO_nilobject);  /* global variable */
	addbuff(buff, p, &lua_newstate);  /* public function */
	lua_assert(p == sizeof(buff));
	return luaS_hash(buff, p, h);
}


/*
** set GCdebt to a new value keeping the value (totalbytes + GCdebt)
** invariant (and avoiding underflows in 'totalbytes')
*/
void luaE_setdebt(global_State* g, l_mem debt) {
	l_mem tb = gettotalbytes(g);
	lua_assert(tb > 0);
	if (debt < tb - MAX_LMEM)
		debt = tb - MAX_LMEM;  /* will make 'totalbytes == MAX_LMEM' */
	g->totalbytes = tb - debt;
	g->GCdebt = debt;
}


CallInfo* luaE_extendCI(lua_State* L) {
	CallInfo* ci = luaM_new(L, CallInfo);
	lua_assert(L->ci->next == NULL);
	L->ci->next = ci;
	ci->previous = L->ci;
	ci->next = NULL;
	L->nci++;
	return ci;
}


/*
** free all CallInfo structures not in use by a thread
*/
void luaE_freeCI(lua_State* L) {
	CallInfo* ci = L->ci;
	CallInfo* next = ci->next;
	ci->next = NULL;
	while ((ci = next) != NULL) {
		next = ci->next;
		luaM_free(L, ci);
		L->nci--;
	}
}


/*
** free half of the CallInfo structures not in use by a thread
*/
void luaE_shrinkCI(lua_State* L) {
	CallInfo* ci = L->ci;
	CallInfo* next2;  /* next's next */
	/* while there are two nexts */
	while (ci->next != NULL && (next2 = ci->next->next) != NULL) {
		luaM_free(L, ci->next);  /* free next */
		L->nci--;
		ci->next = next2;  /* remove 'next' from the list */
		next2->previous = ci;
		ci = next2;  /* keep next's next */
	}
}


/// <summary>
/// 创建一个具有初始状态的 Lua 栈，包括栈的大小、栈顶、栈底、CallInfo 结构体等，并对栈进行一些初始化操作。
/// </summary>
/// <param name="L1"></param>
/// <param name="L"></param>
static void stack_init(lua_State* L1, lua_State* L) {
	int i; CallInfo* ci;
	/* initialize stack array */
	// 分配一个大小为 BASIC_STACK_SIZE(40) 的 TValue 数组，并将其赋值给 L1->stack 字段。TValue 是 Lua 中表示值的结构体类型。
	L1->stack = luaM_newvector(L, BASIC_STACK_SIZE, TValue);
	// 将 BASIC_STACK_SIZE 赋值给 L1->stacksize 字段，表示栈的大小
	L1->stacksize = BASIC_STACK_SIZE;
	// 使用一个循环遍历栈数组，并通过 setnilvalue(L1->stack + i) 将每个栈元素设置为 nil 值，以清空新栈的内容
	for (i = 0; i < BASIC_STACK_SIZE; i++)
		setnilvalue(L1->stack + i);  /* erase new stack */
	// 将 L1->top 设置为 L1->stack，表示栈的顶部。
	L1->top = L1->stack;
	// 通过计算 L1->stack + L1->stacksize - EXTRA_STACK，计算出栈的最后一个元素的位置，并将其赋值给 L1->stack_last 字段。栈顶默认到35，空出5个做buf
	L1->stack_last = L1->stack + L1->stacksize - EXTRA_STACK;
	/* initialize first ci */
	// 将 L1->base_ci 赋值给 ci，L1->base_ci 是 lua_State 结构体中的一个字段，表示第一个 CallInfo 结构体。
	ci = &L1->base_ci;
	// 将 ci->next 和 ci->previous 都设置为 NULL，表示当前 ci 是链表中的首个元素，且没有前一个或后一个元素。
	ci->next = ci->previous = NULL;
	// 将 ci->callstatus 设置为 0，表示没有特殊的调用状态。
	ci->callstatus = 0;
	// 将 L1->top 赋值给 ci->func 字段，表示该 ci 对应的函数在栈中的位置。
	ci->func = L1->top;
	// 接着，通过 setnilvalue(L1->top++) 将 L1->top 所指向的栈元素设置为 nil 值，并将 L1->top 自增。
	setnilvalue(L1->top++);  /* 'function' entry for this 'ci' */
	// 最后，将 L1->top + LUA_MINSTACK 赋值给 ci->top 字段，
	// 表示该 ci 的栈顶位置（ci->top）在当前栈顶位置（L1->top）的基础上再增加 LUA_MINSTACK。
	ci->top = L1->top + LUA_MINSTACK;
	// 将 ci 赋值给 L1->ci 字段，表示当前的 CallInfo 结构体
	L1->ci = ci;
}


static void freestack(lua_State* L) {
	if (L->stack == NULL)
		return;  /* stack not completely built yet */
	L->ci = &L->base_ci;  /* free the entire 'ci' list */
	luaE_freeCI(L);
	lua_assert(L->nci == 0);
	luaM_freearray(L, L->stack, L->stacksize);  /* free stack array */
}


/*
** Create registry table and its predefined values
*/
static void init_registry(lua_State* L, global_State* g) {
	TValue temp;
	/* create registry */
	Table* registry = luaH_new(L);
	sethvalue(L, &g->l_registry, registry);
	luaH_resize(L, registry, LUA_RIDX_LAST, 0);
	/* registry[LUA_RIDX_MAINTHREAD] = L */
	setthvalue(L, &temp, L);  /* temp = L */
	luaH_setint(L, registry, LUA_RIDX_MAINTHREAD, &temp);
	/* registry[LUA_RIDX_GLOBALS] = table of globals */
	sethvalue(L, &temp, luaH_new(L));  /* temp = new table (global table) */
	luaH_setint(L, registry, LUA_RIDX_GLOBALS, &temp);
}


/*
** open parts of the state that may cause memory-allocation errors.
** ('g->version' != NULL flags that the state was completely build)
** 完成 Lua 环境的初始化工作，包括栈的初始化、全局状态的初始化、字符串表、类型表和词法分析器的初始化，
** 还有一些其他的操作，如启用垃圾回收和调用用户自定义的入口函数。
*/
static void f_luaopen(lua_State* L, void* ud) {
	global_State* g = G(L);
	UNUSED(ud);
	stack_init(L, L);  /* init stack */
	init_registry(L, g);
	luaS_init(L);
	luaT_init(L);
	luaX_init(L);
	g->gcrunning = 1;  /* allow gc */
	g->version = lua_version(NULL);
	luai_userstateopen(L);
}


/*
** preinitialize a thread with consistent values without allocating
** any memory (to avoid errors)
*/
static void preinit_thread(lua_State* L, global_State* g) {
	G(L) = g;
	L->stack = NULL;
	L->ci = NULL;
	L->nci = 0;
	L->stacksize = 0;
	L->twups = L;  /* thread has no upvalues */
	L->errorJmp = NULL;
	L->nCcalls = 0;
	L->hook = NULL;
	L->hookmask = 0;
	L->basehookcount = 0;
	L->allowhook = 1;
	resethookcount(L);
	L->openupval = NULL;
	L->nny = 1;
	L->status = LUA_OK;
	L->errfunc = 0;
}


static void close_state(lua_State* L) {
	global_State* g = G(L);
	luaF_close(L, L->stack);  /* close all upvalues for this thread */
	luaC_freeallobjects(L);  /* collect all objects */
	if (g->version)  /* closing a fully built state? */
		luai_userstateclose(L);
	luaM_freearray(L, G(L)->strt.hash, G(L)->strt.size);
	freestack(L);
	lua_assert(gettotalbytes(g) == sizeof(LG));
	(*g->frealloc)(g->ud, fromstate(L), sizeof(LG), 0);  /* free main block */
}


LUA_API lua_State* lua_newthread(lua_State* L) {
	global_State* g = G(L);
	lua_State* L1;
	lua_lock(L);
	luaC_checkGC(L);
	/* create new thread */
	L1 = &cast(LX*, luaM_newobject(L, LUA_TTHREAD, sizeof(LX)))->l;
	L1->marked = luaC_white(g);
	L1->tt = LUA_TTHREAD;
	/* link it on list 'allgc' */
	L1->next = g->allgc;
	g->allgc = obj2gco(L1);
	/* anchor it on L stack */
	setthvalue(L, L->top, L1);
	api_incr_top(L);
	preinit_thread(L1, g);
	L1->hookmask = L->hookmask;
	L1->basehookcount = L->basehookcount;
	L1->hook = L->hook;
	resethookcount(L1);
	/* initialize L1 extra space */
	memcpy(lua_getextraspace(L1), lua_getextraspace(g->mainthread),
		LUA_EXTRASPACE);
	luai_userstatethread(L, L1);
	stack_init(L1, L);  /* init stack */
	lua_unlock(L);
	return L1;
}


void luaE_freethread(lua_State* L, lua_State* L1) {
	LX* l = fromstate(L1);
	luaF_close(L1, L1->stack);  /* close all upvalues for this thread */
	lua_assert(L1->openupval == NULL);
	luai_userstatefree(L, L1);
	freestack(L1);
	luaM_free(L, l);
}


/// <summary>
/// 分配lua_State和global_State
/// 说明：global_State全局表会挂载在lua_State结构上，此方法分配的是主线程栈。如果实现协程，则通过lua_newthread分配新的lua_State栈
/// 通过LG结构方式，每个线程会独立维护自己的线程栈和函数栈
/// 对外通过lua_State结构暴露给用户，而global_State挂载在lua_State结构上
/// 该函数的主要步骤：
///		1.调用内存分配器函数 f 分配一块内存，并将其强制转换为 LG 结构体指针。如果内存分配失败，则返回空指针。
///		2.初始化 lua_State 结构体和 global_State 结构体。
///		3.设置 lua_State 的初始值，包括 next 字段和类型标记。
///		4.设置 global_State 的初始值，包括 GC 相关的字段、内存分配器函数和用户数据、主线程指针、随机种子等。
///		5.执行预初始化线程的操作。
///		6.初始化字符串表和全局注册表。
///		7.设置 GC 状态和类型。
///		8.初始化 GC 相关的链表。
///		9.设置 GC 暂停和步长倍数。
///		10.初始化元方法表。
///		11.调用 luaD_rawrunprotected 执行 f_luaopen 函数进行初始化。如果初始化失败，则释放部分状态，并返回空指针。
/// </summary>
/// <param name="f"></param>
/// <param name="ud"></param>
/// <returns></returns>
LUA_API lua_State* lua_newstate(lua_Alloc f, void* ud) {
	int i;
	lua_State* L;
	global_State* g;
	// 分配一块lua_State结构的内容块
	LG* l = cast(LG*, (*f)(ud, NULL, LUA_TTHREAD, sizeof(LG)));
	if (l == NULL) return NULL;

	/* 初始化 lua_State 结构体和 global_State 结构体 */
	L = &l->l.l;
	g = &l->g;
	L->next = NULL;
	L->tt = LUA_TTHREAD;
	g->currentwhite = bitmask(WHITE0BIT);
	L->marked = luaC_white(g);
	preinit_thread(L, g);

	/* 设置内存分配器和用户数据 */
	g->frealloc = f;
	g->ud = ud;
	// 设置主线程
	g->mainthread = L;
	// 生成随机种子
	g->seed = makeseed(L);
	// GC 处于暂停状态
	g->gcrunning = 0;  /* no GC while building state  */
	// GC 估算值
	g->GCestimate = 0;
	/* 字符串表初始化 */
	g->strt.size = g->strt.nuse = 0;
	g->strt.hash = NULL;

	// 全局注册表置空
	setnilvalue(&g->l_registry);

	g->panic = NULL;
	g->version = NULL;

	// GC 状态设置为 GCSpause（暂停）
	g->gcstate = GCSpause;
	// GC 类型设置为 KGC_NORMAL
	g->gckind = KGC_NORMAL;
	/* GC 链表初始化 */
	g->allgc = g->finobj = g->tobefnz = g->fixedgc = NULL;
	g->sweepgc = NULL;
	g->gray = g->grayagain = NULL;
	g->weak = g->ephemeron = g->allweak = NULL;

	g->twups = NULL;
	g->totalbytes = sizeof(LG);
	g->GCdebt = 0;
	g->gcfinnum = 0;

	/* GC 暂停和步长倍数的设置 */
	g->gcpause = LUAI_GCPAUSE;
	g->gcstepmul = LUAI_GCMUL;

	// 初始化元方法表
	for (i = 0; i < LUA_NUMTAGS; i++) g->mt[i] = NULL;

	// 通过 luaD_rawrunprotected 执行 f_luaopen 函数进行初始化
	if (luaD_rawrunprotected(L, f_luaopen, NULL) != LUA_OK) {
		/* memory allocation error: free partial state */
		close_state(L);
		L = NULL;
	}
	return L;
}


LUA_API void lua_close(lua_State* L) {
	L = G(L)->mainthread;  /* only the main thread can be closed */
	lua_lock(L);
	close_state(L);
}


