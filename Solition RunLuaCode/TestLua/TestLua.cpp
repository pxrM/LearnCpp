/*
*
*   2022/8/1
*/

#include <iostream>
#include <string>
#include "Student.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std;


/*
* lua规定调用注册过的c函数的形式是typedef int (*lua_CFunction) (lua_State *L);
  也就是普通C函数，还要经过变形转成lua_CFunction这种形式，才可以注册到lua中，然后被调用，
  反过来想想也是，普通C函数可没有统一形式，也无法直接用一种方式描式。
*/

// 普通的CCode_MyAdd两个数字相加函数，无法直接注册到lua中
extern "C" long long CCode_MyAdd(long long a, long long b)
{
	return a + b;
}
// 转成lua_CFunction形式为pcf_CCode_MyAdd
extern "C" int pcf_CCode_MyAdd(lua_State * lua)
{
	long long n1 = lua_tointeger(lua, -1);
	long long n2 = lua_tointeger(lua, -2);
	long long iRet = CCode_MyAdd(n2, n1);
	lua_pushinteger(lua, iRet);

	return 1;
}

/// <summary>
/// LUA调用C函数
/// </summary>
void Test_CCode_For_Lua()
{
	cout << "--------------- test c code for lua -------------" << endl;
	// 创建一个 lua 虚拟机
	lua_State* lua = luaL_newstate();
	// 注册库对象到 lua 虚拟机中
	luaL_openlibs(lua);
	// 将c函数注册到lua全局变
	lua_register(lua, "CCode_MyAdd", pcf_CCode_MyAdd);
	// 将字符串转为lua文件并解析执行
	luaL_dostring(lua, "print(\"lua add:\" .. CCode_MyAdd(100, 1000))");


	cout << "--------------- test c code for lua  访问与修改lua变量  -------------" << endl;
	/* 调用lua函数 */
	if (luaL_dofile(lua, "../ccode.lua"))
		cout << lua_tostring(lua, -1) << endl;
	// 通过lua_getglobal这个API获取lua函数，并将其压入虚拟栈
	lua_getglobal(lua, "LuaFileAdd");
	// 压入参数
	lua_pushinteger(lua, 100);
	lua_pushinteger(lua, 900);
	// 调用lua_call(L,n,r)这样的宏接口，进行调用，告知虚拟机，函数有n个参数，r个返回值
	lua_call(lua, 2, 1);
	// 调用完成后，lua会将返回值压入栈，C / C++那端就可以通过类似lua_tonumber这样的API来读取函数返回值
	cout << "lua file function ret: " << lua_tointeger(lua, -1) << endl;
	lua_pop(lua, 1);	// 让栈回到原始状态

	/* 访问lua中的数据 */
	lua_getglobal(lua, "LuaFileStr");
	cout << "lua file str: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "LuaFileTable");
	lua_getfield(lua, -1, "name");
	cout << "lua file table name: " << lua_tostring(lua, -1) << endl;
	lua_getfield(lua, -2, "age");
	cout << "lua file table age: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "ShowTable");
	lua_call(lua, 0, 0);

	/* 修改lua中的数据 */
	lua_pushstring(lua, "XiaoM");
	lua_setfield(lua, 2, "name");
	lua_getfield(lua, 2, "name");
	cout << "lua file new table name: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "ShowTable");
	lua_call(lua, 0, 0);

	lua_close(lua);
	cout << "--------------- test c code for lua -------------" << endl;
}


/*---------------------------------------------------------------------------------------------------------------*/


/// <summary>
/// C/C++调用lua函数
/// </summary>
void Test_Lua_For_CCode()
{
	cout << "--------------- test lua for c code -------------" << endl;

	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);

	// lua加载字符，生成lua全局函数LuaCode_MyAdd
	luaL_dostring(lua, "function LuaCode_MyAdd (x,y) returun x+y end");
	//lua_setglobal(lua, "function LuaCode_MyAdd (x,y) returun x+y end");
	// lua栈压入数据
	lua_getglobal(lua, "LuaCode_MyAdd");
	lua_pushinteger(lua, 100);
	lua_pushinteger(lua, 200);
	// c调用lua中的函数， 2个传入参数, 1个返回值
	lua_call(lua, 2, 1);
	cout << "lua function ret: " << lua_tointeger(lua, -1) << endl;
	lua_pop(lua, 1);

	lua_close(lua);

	cout << "--------------- test lua for c code -------------" << endl;
}


/*---------------------------------------------------------------------------------------------------------------*/


// 从Lua中获取名为"Student"的userdata
Student* GetStudent(lua_State* lua, int arg)
{
	// 检查给定参数索引处的值是否是userdata类型。如果不是userdata类型，将抛出Lua错误。
	luaL_checktype(lua, arg, LUA_TUSERDATA);
	// 检查给定参数索引处的值是否是通过C API注册的类型为"Student"的userdata。它返回userdata的内存地址。
	void* userdata = luaL_checkudata(lua, arg, "Student");
	// 检查userdata是否为非空值。如果userdata为空，将抛出Lua错误。
	luaL_argcheck(lua, userdata != NULL, 1, "user data error");
	// 将userdata的内存地址转换为指向指针的指针，并解引用它以获取指向Student对象的指针。然后将该指针作为返回值返回给Lua。
	return *(Student**)userdata;
}

int pcf_CreateStudentClassToLua(lua_State* lua)
{
	// 从lua栈中把构造参数提取出来
	int age = (int)luaL_checkinteger(lua, 1);
	string name = luaL_checkstring(lua, 2);
	int schoolNum = (int)luaL_checkinteger(lua, 3);
	int classNum = (int)luaL_checkinteger(lua, 4);

	// 使用 lua_newuserdata 在 Lua 堆栈上创建一个新的用户数据对象，并使用双重指针 Student** 来存储用户数据对象的地址。
	//		在 C++ 中，指针是一种特殊的数据类型，可以用来存储对象的内存地址。
	//		当我们需要在函数之间传递指针，并在被调用的函数中修改指针指向的对象时，通常需要使用指针的指针（即双重指针）。
	//		ppStu 是一个双重指针，它存储了 Student 对象的指针的地址。我们实际上将 Student 对象的地址存储在 ppStu 指向的地址上。
	//		为什么要使用双重指针而不是单个指针？
	//		这是因为我们希望在 Lua 中持有 Student 对象的指针，并通过这个指针来访问 Student 对象的属性和方法。
	//		Lua 作为脚本语言，在与 C++ 交互时需要将对象的引用（指针）传递给 Lua 环境。
	//		通过使用双重指针，我们可以在 Lua 中持有一个指向 Student 对象的指针，并在需要时通过解引用操作访问该对象。
	Student** ppStu = (Student**)lua_newuserdata(lua, sizeof(Student*));
	(*ppStu) = new Student(age, name, schoolNum, classNum);

	// 使用 luaL_getmetatable 获取名为 "Student" 的元表
	luaL_getmetatable(lua, "Student");
	// 使用 lua_setmetatable 将刚创建的用户数据对象的元表设置为获取到的 "Student" 元表。
	lua_setmetatable(lua, -2);

	return 1;
}

int pcf_DeleteStudentClassToLua(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	if (pStu)
	{
		cout << "delete student" << endl;
		delete pStu;
	}
	return 1;
}

int pcf_SetAge(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	luaL_checktype(lua, -1, LUA_TUSERDATA);
	int age = (int)luaL_checkinteger(lua, -1);
	pStu->SetAge(age);

	return 0;
}
int pcf_GetAge(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	const int age = pStu->GetAge();
	lua_pushinteger(lua, age);

	return 1;
}

int pcf_GetName(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	const string& name = pStu->GetName();
	lua_pushstring(lua, name.c_str());

	return 1;
}
int pcf_SetName(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	luaL_checktype(lua, -1, LUA_TSTRING);
	string name = luaL_checkstring(lua, -1);
	pStu->SetName(name);

	return 0;
}

int pcf_ShowSelfInfo(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	pStu->ShowSelfInfo();

	return 0;
}

static const luaL_Reg method[] = {
	{"SetAge", pcf_SetAge},
	{"GetAge", pcf_GetAge},
	{"GetName", pcf_GetName},
	{"SetName", pcf_SetName},
	{"ShowSelfInfo", pcf_ShowSelfInfo},
	{"Student", pcf_CreateStudentClassToLua},
	{"__gc", pcf_DeleteStudentClassToLua},
	{NULL, NULL},
};

// 在Lua中注册名为"Student"的元表
int luaOpenStudent(lua_State* lua)
{
	// lua中luaL_newmetatable创建名为Student元表metatable
	//	栈变化：[元表]
	luaL_newmetatable(lua, "Student"); 

	// 将栈顶的值（即刚创建的元表）复制一份，并将复制的值压入栈顶。
	// 此时，堆栈上有两个相同的元表：原始的元表和复制的元表。
	//	 为什么要复制元表？这是因为在元表中定义的方法通常需要在实例对象上进行操作，
	//	 而实例对象通常会使用元表作为其原型，以便继承元表中的方法，通过在堆栈上保留一份元表的副本，
	//	 可以方便地在之后的代码引用该元表。
	//	 简而言之，通过复制元表并将其设置为原始元表的 "__index" 字段，
	//	 我们能够实现对象的属性和方法的继承，并确保每个对象都有独立的属性和方法。这样做是为了更好地管理对象的行为和状态，
	//	 提供了更灵活的编程方式。
	// 栈变化：[元表, 元表副本]
	lua_pushvalue(lua, -1);

	// 将复制出来的元表设置为原始元表的 "__index" 字段
	//	 栈变化：[元表]
	lua_setfield(lua, -2, "__index");

	// 将指定的函数列表 method 中的方法注册到原始元表中，使得对象能够调用这些方法。
	luaL_setfuncs(lua, method, 0);

	return 1;
}

static const luaL_Reg libs[] = {
	{"Student", luaOpenStudent},
	{NULL, NULL},
};

void luaRegisterCppStudentLibs(lua_State* lua)
{
	const luaL_Reg* lib = libs;
	for (; lib->func; lib++)
	{
		luaL_requiref(lua, lib->name, lib->func, 1);
		lua_pop(lua, 1);
	}
}
 

void Test_CPP_Code()
{
	cout << endl << endl << endl << "---------------- test cpp code for lua--------------------" << endl;

	lua_State* lua = luaL_newstate();
	luaopen_base(lua);
	luaRegisterCppStudentLibs(lua);
	luaL_dofile(lua, "../student.lua");
	lua_close(lua);

	cout << "---------------- test cpp code for lua--------------------" << endl;
}

int main()
{
	std::cout << "Hello World!\n";
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	_CrtSetDebugFillThreshold(0);
#endif

	cout << "hello lua and c/c++" << endl;

	Test_CCode_For_Lua();
	//Test_Lua_For_CCode();
	Test_CPP_Code();

	system("pause");
}


