/*
** $Id: lstate.h,v 2.133.1.1 2017/04/19 17:39:34 roberto Exp $
** Global State
** See Copyright Notice in lua.h
*/

#ifndef lstate_h
#define lstate_h

#include "lua.h"

#include "lobject.h"
#include "ltm.h"
#include "lzio.h"


/*

** Some notes about garbage-collected objects: All objects in Lua must
** be kept somehow accessible until being freed, so all objects always
** belong to one (and only one) of these lists, using field 'next' of
** the 'CommonHeader' for the link:
**
** 'allgc': all objects not marked for finalization;
** 'finobj': all objects marked for finalization;
** 'tobefnz': all objects ready to be finalized;
** 'fixedgc': all objects that are not to be collected (currently
** only small strings, such as reserved words).
**
** Moreover, there is another set of lists that control gray objects.
** These lists are linked by fields 'gclist'. (All objects that
** can become gray have such a field. The field is not the same
** in all objects, but it always has this name.)  Any gray object
** must belong to one of these lists, and all objects in these lists
** must be gray:
**
** 'gray': regular gray objects, still waiting to be visited.
** 'grayagain': objects that must be revisited at the atomic phase.
**   That includes
**   - black objects got in a write barrier;
**   - all kinds of weak tables during propagation phase;
**   - all threads.
** 'weak': tables with weak values to be cleared;
** 'ephemeron': ephemeron tables with white->white entries;
** 'allweak': tables with weak keys and/or weak values to be cleared.
** The last three lists are used only during the atomic phase.

*/


struct lua_longjmp;  /* defined in ldo.c */


/*
** Atomic type (relative to signals) to better ensure that 'lua_sethook'
** is thread safe
*/
#if !defined(l_signalT)
#include <signal.h>
#define l_signalT	sig_atomic_t
#endif


/* extra stack space to handle TM calls and some other extras */
#define EXTRA_STACK   5


#define BASIC_STACK_SIZE        (2*LUA_MINSTACK)


/* kinds of Garbage Collection */
#define KGC_NORMAL	0
#define KGC_EMERGENCY	1	/* gc was forced by an allocation failure  紧急类型，表示在程序发生错误或内存不足时的紧急 GC。 */


typedef struct stringtable {
	TString** hash;
	int nuse;  /* number of elements */
	int size;
} stringtable;


/*
** Information about a call.
** When a thread yields, 'func' is adjusted to pretend that the
** top function has only the yielded values in its stack; in that
** case, the actual 'func' value is saved in field 'extra'.
** When a function calls another with a continuation, 'extra' keeps
** the function index so that, in case of errors, the continuation
** function can be called with the correct top.
* 
* 表示函数调用的信息，包括函数索引、栈顶位置、动态调用链等。
*/
typedef struct CallInfo {
	StkId func;  /* function index in the stack  函数在栈中的索引。 */
	StkId	top;  /* top for this function  该函数的栈顶位置。 */
	struct CallInfo* previous, * next;  /* dynamic call link  用于构建动态调用链的指针，指向上一个和下一个 CallInfo 结构体。 */
	// 一个联合体，用于区分 Lua 函数和 C 函数的不同信息。
	union {
		struct {  /* only for Lua functions	   如果是 Lua 函数，包含 l 结构体： */
			StkId base;  /* base for this function	 函数的基地址，在栈中表示该函数的第一个参数。 */
			const Instruction* savedpc;	/*  保存的程序计数器，用于记录函数执行的进度。 */
		} l;
		struct {  /* only for C functions  如果是 C 函数，包含 c 结构体： */
			lua_KFunction k;  /* continuation in case of yields		继续执行的回调函数，用于处理协程的恢复操作。 */
			ptrdiff_t old_errfunc;	/*  旧的错误处理函数。 */
			lua_KContext ctx;  /* context info. in case of yields	上下文信息，在协程的恢复操作中使用。 */ 
		} c;
	} u;
	ptrdiff_t extra;	/* 额外的字段，用于存储其他信息。 */
	short nresults;  /* expected number of results from this function  期望从该函数返回的结果数量。 */
	unsigned short callstatus;	/* 调用状态的标志位。 */
} CallInfo;


/*
** Bits in CallInfo status
*/
#define CIST_OAH	(1<<0)	/* original value of 'allowhook' */
#define CIST_LUA	(1<<1)	/* call is running a Lua function */
#define CIST_HOOKED	(1<<2)	/* call is running a debug hook */
#define CIST_FRESH	(1<<3)	/* call is running on a fresh invocation
								   of luaV_execute */
#define CIST_YPCALL	(1<<4)	/* call is a yieldable protected call */
#define CIST_TAIL	(1<<5)	/* call was tail called */
#define CIST_HOOKYIELD	(1<<6)	/* last hook called yielded */
#define CIST_LEQ	(1<<7)  /* using __lt for __le */
#define CIST_FIN	(1<<8)  /* call is running a finalizer */

#define isLua(ci)	((ci)->callstatus & CIST_LUA)

								   /* assume that CIST_OAH has offset 0 and that 'v' is strictly 0/1 */
#define setoah(st,v)	((st) = ((st) & ~CIST_OAH) | (v))
#define getoah(st)	((st) & CIST_OAH)


/*
** 'global state', shared by all threads of this state
*	全局状态机，由该状态的所有线程共享
*	作用：管理全局数据，全局字符串表、内存管理函数、 GC 把所有对象串联起来的信息、内存等
*/
typedef struct global_State {
	const lua_Number* version;  /* pointer to version number  版本号的指针 */

	/* 内存管理 */
	lua_Alloc frealloc;  /* function to reallocate memory  Lua的全局内存分配器（重新分配内存的函数），用户可以替换成自己的 */
	void* ud;         /* auxiliary data to 'frealloc'  这是一个通用指针，可以指向任何类型，通常用于存储 frealloc 函数的辅助数据 */

	/* 线程管理 */
	struct lua_State* mainthread;  /* 主线程的状态 */
	struct lua_State* twups;  /* list of threads with open upvalues  带有打开的 upvalues 的线程列表 */

	/* 字符串管理 */
	stringtable strt;  /* hash table for strings  字符串table，Lua的字符串分短字符串和长字符串 */
	TString* strcache[STRCACHE_N][STRCACHE_M];  /* cache for strings in API  字符串缓存 */

	/* 虚函数表 */
	TString* tmname[TM_N];  /* array with tag-method names	预定义方法名字数组 */
	struct Table* mt[LUA_NUMTAGS];  /* metatables for basic types  每个基本类型一个metatable（整个Lua最重要的Hook机制） */

	/* 错误处理 */
	lua_CFunction panic;  /* to be called in unprotected errors		在未受保护的错误中调用函数 */
	TString* memerrmsg;  /* memory-error message  内存错误信息 */

	l_mem totalbytes;  /* number of bytes currently allocated - GCdebt  表示当前分配的字节数，包括由于未偿还的 GCdebt 而尚未释放的字节数 */
	l_mem GCdebt;  /* bytes allocated not yet compensated by the collector  表示尚未由垃圾收集器偿还的已分配字节数。
	当 Lua 分配内存时，它会先从 GCdebt 中扣除相应的字节数，然后再将剩余的字节数添加到 totalbytes 中。
	当 GC 运行时，它会尝试回收一部分内存，并将回收的字节数添加到 GCdebt 中。 */
	lu_mem GCmemtrav;  /* memory traversed by the GC	表示 GC 遍历的内存字节数。在垃圾回收过程中，
	GC 会遍历堆中的所有对象，并确定哪些对象仍然被引用。GCmemtrav 字段记录了 GC 在遍历阶段所经过的内存字节数，用于统计和诊断目的。 */
	lu_mem GCestimate;  /* an estimate of the non-garbage memory in use  表示当前正在使用的非垃圾内存的估计值。
	GCestimate 是根据遍历阶段的结果计算得出的，它代表了 GC 认为当前没有被回收的内存量。
	这个估计值可能不太准确，但通常用于监视和诊断内存使用情况。 */

	TValue l_registry;  /* 全局注册表 table 存储一些全局属性、函数、模块等，以及跨多个 Lua 状态之间共享的数据 */
	unsigned int seed;  /* randomized seed for hashes	随机化哈希种子。用作随机数发生器的种子。 */
	lu_byte currentwhite;  /* 表示当前的 GC 白色标记。GC 分为几个阶段，其中白色标记表示需要进行垃圾收集的对象。*/
	lu_byte gcstate;  /* state of garbage collector	 垃圾收集器状态 */
	lu_byte gckind;  /* kind of GC running	GC运行类型：KGC_NORMAL：表示通常的 GC。KGC_EMERGENCY：在程序发生错误或内存不足时的紧急 GC。 */
	lu_byte gcrunning;  /* true if GC is running GC是否正在运行 */
	GCObject* allgc;  /* list of all collectable objects  所有可收集对象的列表 */
	GCObject** sweepgc;  /* current position of sweep in list	表示待扫描的对象链表。 */
	GCObject* finobj;  /* list of collectable objects with finalizers   带有终结器的可收集对象列表 */
	GCObject* gray;  /* list of gray objects  灰色物体列表 */
	GCObject* grayagain;  /* list of objects to be traversed atomically	 表示再次遍历的灰色对象链表。 */
	GCObject* weak;  /* list of tables with weak values  具有弱值的表列表 */
	GCObject* ephemeron;  /* list of ephemeron tables (weak keys)  临时表列表(弱键) */
	GCObject* allweak;  /* list of all-weak tables   所有弱表的列表 */
	GCObject* tobefnz;  /* list of userdata to be GC   要GC的用户数据列表 */
	GCObject* fixedgc;  /* list of objects not to be collected  不被收集的对象列表 */


	/* GC管理 */
	unsigned int gcfinnum;  /* number of finalizers to call in each GC step */
	int gcpause;  /* size of pause between successive GCs */
	int gcstepmul;  /* GC 'granularity' */

} global_State;


/*
** 'per thread' state
	每个线程的栈数据结构
	作用：管理整个栈和当前函数使用的栈的情况，最主要的功能就是函数调用以及和c的通信
*/
struct lua_State {
	CommonHeader; /* 通用头部，包含了垃圾收集器需要的信息。 */

	/* 解析容器的用于记录中间状态*/
	lu_byte status;

	/* 全局状态机 */
	global_State* l_G;

	/* 调用栈：调用栈信息管理（CallInfo 为双向链表结构） */
	unsigned short nci;  /* number of items in 'ci' list	存储一共多少个CallInfo */
	CallInfo base_ci;  /* CallInfo for first level (C calling Lua)	  调用栈的头部指针 */
	CallInfo* ci;  /* call info for current function	 当前运行函数信息 */

	/* 数据栈：栈指针地址管理 StkId = TValue 的数组 */
	StkId top;  /* first free slot in the stack		线程栈的第一个空闲位置指针 */
	StkId stack_last;  /* last free slot in the stack	线程栈的最后一个空闲位置 */
	StkId stack;  /* stack base	 栈的指针，当前执行的位置 */

	const Instruction* oldpc;  /* last pc traced	在当前thread 的解释执行指令的过程中，指向最后一次执行的指令的指针 */
	UpVal* openupval;  /* list of open upvalues in this stack   此栈中打开的上值(upvalue)列表 */
	GCObject* gclist;  /* GC列表 */
	struct lua_State* twups;  /* list of threads with open upvalues	 带有打开的 upvalues 的线程列表 */
	struct lua_longjmp* errorJmp;  /* current error recover point	 当前的错误恢复点 */

	/* Hook 相关管理 - 服务于debug模块 */
	volatile lua_Hook hook;  /* 钩子函数 */
	ptrdiff_t errfunc;  /* current error handling function (stack index)  第一级别的 CallInfo（C 调用 Lua） */
	int stacksize;	/* 栈的大小 */
	int basehookcount;	/* 钩子函数的计数器 */
	int hookcount;	/* 钩子函数的计数器 */
	l_signalT hookmask;	/* 钩子掩码 */
	lu_byte allowhook;	/* 是否允许钩子 */

	/* 跟C语言通信 管理*/
	unsigned short nny;  /* number of non-yieldable calls in stack  栈中非可中断调用的数量 */
	unsigned short nCcalls;  /* number of nested C calls   嵌套的 C 调用数量 */
};


#define G(L)	(L->l_G)


/*
** Union of all collectable objects (only for conversions)
*/
union GCUnion {
	GCObject gc;  /* common header */
	struct TString ts;
	struct Udata u;
	union Closure cl;
	struct Table h;
	struct Proto p;
	struct lua_State th;  /* thread */
};


#define cast_u(o)	cast(union GCUnion *, (o))

/* macros to convert a GCObject into a specific value */
#define gco2ts(o)  \
	check_exp(novariant((o)->tt) == LUA_TSTRING, &((cast_u(o))->ts))
#define gco2u(o)  check_exp((o)->tt == LUA_TUSERDATA, &((cast_u(o))->u))
#define gco2lcl(o)  check_exp((o)->tt == LUA_TLCL, &((cast_u(o))->cl.l))
#define gco2ccl(o)  check_exp((o)->tt == LUA_TCCL, &((cast_u(o))->cl.c))
#define gco2cl(o)  \
	check_exp(novariant((o)->tt) == LUA_TFUNCTION, &((cast_u(o))->cl))
#define gco2t(o)  check_exp((o)->tt == LUA_TTABLE, &((cast_u(o))->h))
#define gco2p(o)  check_exp((o)->tt == LUA_TPROTO, &((cast_u(o))->p))
#define gco2th(o)  check_exp((o)->tt == LUA_TTHREAD, &((cast_u(o))->th))


/* macro to convert a Lua object into a GCObject */
#define obj2gco(v) \
	check_exp(novariant((v)->tt) < LUA_TDEADKEY, (&(cast_u(v)->gc)))


/* actual number of total bytes allocated */
#define gettotalbytes(g)	cast(lu_mem, (g)->totalbytes + (g)->GCdebt)

LUAI_FUNC void luaE_setdebt(global_State* g, l_mem debt);
LUAI_FUNC void luaE_freethread(lua_State* L, lua_State* L1);
LUAI_FUNC CallInfo* luaE_extendCI(lua_State* L);
LUAI_FUNC void luaE_freeCI(lua_State* L);
LUAI_FUNC void luaE_shrinkCI(lua_State* L);


#endif

