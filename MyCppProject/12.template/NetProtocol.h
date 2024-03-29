/*
	·网络协议基础框架

	·遍历任意参（展开方式和递归方式）
	·获取可变参数的数量
	·什么是模板泛化：当前所有模板参数都未定义，只有等到使用的时候知道
	·什么是模板全特化：给定一个确定的类型，前提是要有个泛化的模板
	·通过模板偏特化来获取可变参数的字节大小
	·通过模板循环继承方式展开可变参数
	·通过using循环命名的方式展开可变参数

	·通过工厂来构建任意参数对象
	·支持任意参数的简单代理
*/

#pragma once

#include <iostream>

using namespace std;

typedef unsigned char uint8;


//负责网络消息的类
template<uint8 MessageType> //对应协议号
class NetControlMessage
{

};


//网络信息
class NetControlMessageInfo
{
public:
	// 接受消息函数
	template<typename ... ParamTypes> //支持任意参的模板
	static void ReceiveParams(ParamTypes &... Params)
	{

	}

	// 发送消息函数
	template<typename ... ParamTypes>
	static void SendParams(ParamTypes &... Params)
	{

	}
};

enum //全局枚举
{
	ETest_A = 0,
};

/////////////////////////// 这种方式每增加一个协议号都需要增加一个模板 ///////////////////////////
/*
template<> class NetControlMessage<0>
{
public:
	template<typename ...ParamTypes>
	static void Receive(ParamTypes &... Params)
	{
		NetControlMessageInfo::ReceiveParams(Params...);
	}

	template<typename ...ParamTypes>
	static void Send(ParamTypes &... Params)
	{
		NetControlMessageInfo::SendParams(Params...)
	}
};
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_CONTROL_CHANNEL_MESSAGE(Name, Index, ...) \
enum \
{ \
	NMT_##Name = Index, \
}; \
template<> class NetControlMessage<Index> \
{ \
public: \
	template<typename ...ParamTypes> \
	static void Receive(ParamTypes &... Params) \
	{ \
		NetControlMessageInfo::ReceiveParams(Params...); \
	} \
	template<typename ...ParamTypes> \
	static void Send(ParamTypes &... Params) \
	{ \
		NetControlMessageInfo::SendParams(Params...); \
	} \
};

//定义协议行为
DEFINE_CONTROL_CHANNEL_MESSAGE(Enter, 0, int, float, char)
DEFINE_CONTROL_CHANNEL_MESSAGE(Login, 1, int, char)





/////////////////////////// 遍历任意参（展开方式） ///////////////////////////
template<typename T>
void PrintfArg(T &arg)
{
	cout << arg << endl;
}

template<typename ... ParamTypes>
void FunTest(ParamTypes &... Params)
{
	// std::forward()
	char arr[] = { (PrintfArg(Params), 0)... }; //这里0表示占位，或者在PrintfArg函数加个返回值，这种方式会产生拷贝
	char arr2[] = { (char)Params ... };
}

/////////////////////////// 遍历任意参（递归方式） ///////////////////////////
void FunTest2()
{
	cout << "没有了" << endl;
}
template<typename T, typename ... ParamTypes>
void FunTest2(T &Head, ParamTypes &... Params)
{
	cout << "Head = " << Head << endl;
	FunTest2(Params...);
}

/////////////////////////// 获取可变参数的数量 ///////////////////////////
template<typename ... ParamTypes>
void FunTestLen(ParamTypes &... Params)
{
	cout << sizeof...(Params) << endl;
}

/////////////////////////// 通过可变参数特性求和 ///////////////////////////
template <typename ParamTypes>
ParamTypes &FuncValue(ParamTypes &Param)
{
	return Param;
}
template<typename T, typename ... ParamTypes>
T FuncValue(T &Head, ParamTypes &... Params)
{
	return Head + FuncValue<T>(Params...);
}

/////////////////////////// 什么是模板泛化：当前所有模板参数都未定义，只有等到使用的时候知道 ///////////////////////////
template<class T1, class T2>
class TempTest_Two
{
private:
	T1 Data1;
	T2 Data2;
};

/////////////////////////// 什么是模板全特化：给定一个确定的类型，前提是要有个泛化的模板 ///////////////////////////
template<>
class TempTest_Two<int, float>
{
};

template<class T>
void FuncTempTest()
{
}

template<>
void FuncTempTest<int>() {}

/////////////////////////// 模板偏特化（函数没有偏特化） ///////////////////////////
//通过模板偏特化来获取可变参数的字节大小
template<typename T, class ...ParamTypes>
class TempTestLen
{
public:
	enum
	{
		Num = TempTestLen<T>::Num + TempTestLen<ParamTypes...>::Num,
	};
};

//偏特化
template<typename Last>
class TempTestLen<Last>
{
public:
	enum
	{
		Num = sizeof(Last),
	};
};

#define TEMP_TEST_LEN(Name, ...) TempTestLen<__VA_ARGS__> Name

/////////////////////////// 通过模板循环继承方式展开可变参数 ///////////////////////////
template<int ...>
struct HelloIndex
{

};

template<int N, int...ParamTypes>
struct SpawnIndex :SpawnIndex<N - 1, N - 1, ParamTypes...>
{

};

template<int...ParamTypes>
struct SpawnIndex<0, ParamTypes...>
{
	typedef HelloIndex<ParamTypes...> MType;
};

/////////////////////////// 通过using循环命名的方式展开可变参数 ///////////////////////////
template<int N, int ... ParamTypes>
struct SpawnIndex_Two
{
	using MType_Two = typename SpawnIndex_Two<N - 1, N - 1, ParamTypes...>::MType_Two;
};
//循环终止
template<int...ParamTypes>
struct SpawnIndex_Two<0, ParamTypes...>
{
	typedef SpawnIndex_Two<ParamTypes...> MType_Two;
};

/////////////////////////// 通过工厂来构建任意参数对象 ///////////////////////////
template<class T>
T *CreateObject_NoParam()
{
	return new T();
}

template<class T, typename Arg0>
T *CreateObject_OneParam()
{
	return new T(Arg0);
}

template<class T, typename Arg0, typename Arg1>
T *CreateObject_TwoParam()
{
	return new T(Arg0, Arg1);
}

template<class T, typename ...ParamTypes>
T *CreateObject(ParamTypes &&...Param)
{
	return new T(std::forward<ParamTypes>(Param)...); //使用std::forward避免拷贝
}

struct COTestA
{
};

struct COTestB {
public:
	COTestB(int a, int b)
	{

	}
};

/////////////////////////// 支持任意参数的简单代理 ///////////////////////////
template<class TObjectType, class TReturn, typename ...ParamTypes>
class MDelegate
{
public:
	MDelegate(TObjectType *InObj, TReturn(TObjectType:: *InFunc)(ParamTypes...))
		:Object(InObj)
		, Funcation(InFunc)
	{
	}

	//重载()操作符
	TReturn operator()(ParamTypes &&...Param)
	{
		return (Object->*Funcation)(std::forward<ParamTypes>(Param)...);
	}

private:
	TObjectType *Object;
	TReturn(TObjectType:: *Funcation)(ParamTypes...);
};

template<class TObjectType, class TReturn, typename ...ParamTypes>
MDelegate<TObjectType, TReturn, ParamTypes...>CreateMDelegate(TObjectType *InObj, TReturn(TObjectType:: *InFunc)(ParamTypes...))
{
	return MDelegate<TObjectType, TReturn, ParamTypes...>(InObj, InFunc);
}

struct COTestC {
public:
	COTestC()
	{

	}

	int Print(int a, int b)
	{
		printf("%i, %i \n", a, b);
		return a + b;
	}
};