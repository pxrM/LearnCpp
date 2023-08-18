/*
*
*   2022/8/1
*/

#include <iostream>
#include <string>

#include "Student.h"

using namespace std;

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


extern "C" long long CCode_MyAdd(long long a, long long b)
{
	return a + b;
}

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

	if (luaL_dofile(lua, "../ccode.lua"))
		cout << lua_tostring(lua, -1) << endl;
	// lua中的函数
	lua_getglobal(lua, "LuaFileAdd");
	lua_pushinteger(lua, 100);
	lua_pushinteger(lua, 900);
	lua_call(lua, 2, 1);
	cout << "lua file function ret: " << lua_tointeger(lua, -1) << endl;
	lua_pop(lua, 1);	// 让栈回到原始状态

	// lua中的数据
	lua_getglobal(lua, "LuaFileStr");
	cout << "lua file str: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "LuaFileTable");
	lua_getfield(lua, -1, "name");
	cout << "lua file table name: " << lua_tostring(lua, -1) << endl;
	lua_getfield(lua, -2, "age");
	cout << "lua file table age: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "ShowTable");
	lua_call(lua, 0, 0);

	// 修改
	lua_pushstring(lua, "XiaoM");
	lua_setfield(lua, 2, "name");
	lua_getfield(lua, 2, "name");
	cout << "lua file new table name: " << lua_tostring(lua, -1) << endl;
	lua_getglobal(lua, "ShowTable");
	lua_call(lua, 0, 0);


	lua_close(lua);

	cout << "--------------- test c code for lua -------------" << endl;
}




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





Student* GetStudent(lua_State* lua, int arg)
{
	// 从栈顶取userdata，这个是C++的对象指针
	luaL_checktype(lua, arg, LUA_TUSERDATA);
	void* userdata = luaL_checkudata(lua, arg, "Student");
	luaL_argcheck(lua, userdata != NULL, 1, "user data error");

	return *(Student**)userdata;
}

int pcf_CreateStudentClassToLua(lua_State* lua)
{
	// 将lua栈中构造参数提取出来
	int age = (int)luaL_checkinteger(lua, 1);
	string name = luaL_checkstring(lua, 2);
	int schoolNum = (int)luaL_checkinteger(lua, 3);
	int classNum = (int)luaL_checkinteger(lua, 4);

	// 创建userdata，搞到对象指针
	Student** ppStu = (Student**)lua_newuserdata(lua, sizeof(Student*));
	(*ppStu) = new Student(age, name, schoolNum, classNum);

	// 获取元表
	luaL_getmetatable(lua, "Student");
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

int luaOpenStudent(lua_State* lua)
{
	// lua中luaL_newmetatable创建名为Student元表metatable
	luaL_newmetatable(lua, "Student");
	lua_pushvalue(lua, -1);
	// 通过lua_setfield将__index将其元表设为自己
	lua_setfield(lua, -2, "__index");
	// 通过luaL_setfuncs将method公共方法添加到元表中
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


