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
/// ����һ�����г�ʼ״̬�� Lua ջ������ջ�Ĵ�С��ջ����ջ�ס�CallInfo �ṹ��ȣ�����ջ����һЩ��ʼ��������
/// </summary>
/// <param name="L1"></param>
/// <param name="L"></param>
static void stack_init(lua_State* L1, lua_State* L) {
	int i; CallInfo* ci;
	/* initialize stack array */
	// ����һ����СΪ BASIC_STACK_SIZE(40) �� TValue ���飬�����丳ֵ�� L1->stack �ֶΡ�TValue �� Lua �б�ʾֵ�Ľṹ�����͡�
	L1->stack = luaM_newvector(L, BASIC_STACK_SIZE, TValue);
	// �� BASIC_STACK_SIZE ��ֵ�� L1->stacksize �ֶΣ���ʾջ�Ĵ�С
	L1->stacksize = BASIC_STACK_SIZE;
	// ʹ��һ��ѭ������ջ���飬��ͨ�� setnilvalue(L1->stack + i) ��ÿ��ջԪ������Ϊ nil ֵ���������ջ������
	for (i = 0; i < BASIC_STACK_SIZE; i++)
		setnilvalue(L1->stack + i);  /* erase new stack */
	// �� L1->top ����Ϊ L1->stack����ʾջ�Ķ�����
	L1->top = L1->stack;
	// ͨ������ L1->stack + L1->stacksize - EXTRA_STACK�������ջ�����һ��Ԫ�ص�λ�ã������丳ֵ�� L1->stack_last �ֶΡ�ջ��Ĭ�ϵ�35���ճ�5����buf
	L1->stack_last = L1->stack + L1->stacksize - EXTRA_STACK;
	/* initialize first ci */
	// �� L1->base_ci ��ֵ�� ci��L1->base_ci �� lua_State �ṹ���е�һ���ֶΣ���ʾ��һ�� CallInfo �ṹ�塣
	ci = &L1->base_ci;
	// �� ci->next �� ci->previous ������Ϊ NULL����ʾ��ǰ ci �������е��׸�Ԫ�أ���û��ǰһ�����һ��Ԫ�ء�
	ci->next = ci->previous = NULL;
	// �� ci->callstatus ����Ϊ 0����ʾû������ĵ���״̬��
	ci->callstatus = 0;
	// �� L1->top ��ֵ�� ci->func �ֶΣ���ʾ�� ci ��Ӧ�ĺ�����ջ�е�λ�á�
	ci->func = L1->top;
	// ���ţ�ͨ�� setnilvalue(L1->top++) �� L1->top ��ָ���ջԪ������Ϊ nil ֵ������ L1->top ������
	setnilvalue(L1->top++);  /* 'function' entry for this 'ci' */
	// ��󣬽� L1->top + LUA_MINSTACK ��ֵ�� ci->top �ֶΣ�
	// ��ʾ�� ci ��ջ��λ�ã�ci->top���ڵ�ǰջ��λ�ã�L1->top���Ļ����������� LUA_MINSTACK��
	ci->top = L1->top + LUA_MINSTACK;
	// �� ci ��ֵ�� L1->ci �ֶΣ���ʾ��ǰ�� CallInfo �ṹ��
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
** ��� Lua �����ĳ�ʼ������������ջ�ĳ�ʼ����ȫ��״̬�ĳ�ʼ�����ַ��������ͱ�ʹʷ��������ĳ�ʼ����
** ����һЩ�����Ĳ������������������պ͵����û��Զ������ں�����
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
/// ����lua_State��global_State
/// ˵����global_Stateȫ�ֱ�������lua_State�ṹ�ϣ��˷�������������߳�ջ�����ʵ��Э�̣���ͨ��lua_newthread�����µ�lua_Stateջ
/// ͨ��LG�ṹ��ʽ��ÿ���̻߳����ά���Լ����߳�ջ�ͺ���ջ
/// ����ͨ��lua_State�ṹ��¶���û�����global_State������lua_State�ṹ��
/// �ú�������Ҫ���裺
///		1.�����ڴ���������� f ����һ���ڴ棬������ǿ��ת��Ϊ LG �ṹ��ָ�롣����ڴ����ʧ�ܣ��򷵻ؿ�ָ�롣
///		2.��ʼ�� lua_State �ṹ��� global_State �ṹ�塣
///		3.���� lua_State �ĳ�ʼֵ������ next �ֶκ����ͱ�ǡ�
///		4.���� global_State �ĳ�ʼֵ������ GC ��ص��ֶΡ��ڴ�������������û����ݡ����߳�ָ�롢������ӵȡ�
///		5.ִ��Ԥ��ʼ���̵߳Ĳ�����
///		6.��ʼ���ַ������ȫ��ע���
///		7.���� GC ״̬�����͡�
///		8.��ʼ�� GC ��ص�����
///		9.���� GC ��ͣ�Ͳ���������
///		10.��ʼ��Ԫ������
///		11.���� luaD_rawrunprotected ִ�� f_luaopen �������г�ʼ���������ʼ��ʧ�ܣ����ͷŲ���״̬�������ؿ�ָ�롣
/// </summary>
/// <param name="f"></param>
/// <param name="ud"></param>
/// <returns></returns>
LUA_API lua_State* lua_newstate(lua_Alloc f, void* ud) {
	int i;
	lua_State* L;
	global_State* g;
	// ����һ��lua_State�ṹ�����ݿ�
	LG* l = cast(LG*, (*f)(ud, NULL, LUA_TTHREAD, sizeof(LG)));
	if (l == NULL) return NULL;

	/* ��ʼ�� lua_State �ṹ��� global_State �ṹ�� */
	L = &l->l.l;
	g = &l->g;
	L->next = NULL;
	L->tt = LUA_TTHREAD;
	g->currentwhite = bitmask(WHITE0BIT);
	L->marked = luaC_white(g);
	preinit_thread(L, g);

	/* �����ڴ���������û����� */
	g->frealloc = f;
	g->ud = ud;
	// �������߳�
	g->mainthread = L;
	// �����������
	g->seed = makeseed(L);
	// GC ������ͣ״̬
	g->gcrunning = 0;  /* no GC while building state  */
	// GC ����ֵ
	g->GCestimate = 0;
	/* �ַ������ʼ�� */
	g->strt.size = g->strt.nuse = 0;
	g->strt.hash = NULL;

	// ȫ��ע����ÿ�
	setnilvalue(&g->l_registry);

	g->panic = NULL;
	g->version = NULL;

	// GC ״̬����Ϊ GCSpause����ͣ��
	g->gcstate = GCSpause;
	// GC ��������Ϊ KGC_NORMAL
	g->gckind = KGC_NORMAL;
	/* GC �����ʼ�� */
	g->allgc = g->finobj = g->tobefnz = g->fixedgc = NULL;
	g->sweepgc = NULL;
	g->gray = g->grayagain = NULL;
	g->weak = g->ephemeron = g->allweak = NULL;

	g->twups = NULL;
	g->totalbytes = sizeof(LG);
	g->GCdebt = 0;
	g->gcfinnum = 0;

	/* GC ��ͣ�Ͳ������������� */
	g->gcpause = LUAI_GCPAUSE;
	g->gcstepmul = LUAI_GCMUL;

	// ��ʼ��Ԫ������
	for (i = 0; i < LUA_NUMTAGS; i++) g->mt[i] = NULL;

	// ͨ�� luaD_rawrunprotected ִ�� f_luaopen �������г�ʼ��
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


