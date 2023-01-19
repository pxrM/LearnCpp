/*
	仿函数和代理

		仿函数可以做代理
			ue仿函数：TFunction、TFunctionRef
*/

#include <iostream>
#include <functional>

#include "MProxy.h"


using namespace std;


int FunctorTest(int a, int b)
{
	cout << "FunctorTest" << endl;
	return a + b;
}


auto FunctorLambda = [&](int a, int b)->int
{
	cout << "FunctorLambda" << endl;
	return a + b;
};


int(*FunctorPointer)(int, int);


template<class T>
T FuncTemp(T a, T b)
{
	cout << "FuncTemp" << endl;
	return a + b;
}


void FuncCallBack(function<int(int, int)> func)
{
	cout << "FuncCallBack" << endl;
	int res = func(2, 666);
}


class Test1
{
public:
	int FunctorObj(int a, int b)
	{
		cout << "FunctorObj" << endl;
		return a + b;
	}
};

class Test2
{
public:
	int operator()(int a, int b)
	{
		cout << "operator()" << endl;
		return a + b;
	}

	static int FunctorStatic(int a, int b)
	{
		cout << "FunctorStatic" << endl;
		return a + b;
	}
};



int main()
{
	// 仿函数 
	// <int(int, int)> 函数指针 int返回值  两个int参数
	std::function<int(int, int)> mFunctor1;
	//mFunctor1(1, 1);	//ERR：此时还没有函数实体，所以会崩溃
	//普通函数
	mFunctor1 = FunctorTest;
	int result = mFunctor1(10, 9);
	//Lambda
	mFunctor1 = FunctorLambda;
	result = mFunctor1(999, 9);
	//函数指针
	FunctorPointer = FunctorTest;
	mFunctor1 = FunctorPointer;
	result = mFunctor1(1, 9);
	//对象函数+bind
	Test1 T1;
	mFunctor1 = bind(&Test1::FunctorObj, &T1, placeholders::_1, placeholders::_2);
	result = mFunctor1(1, 9);
	//类函数
	mFunctor1 = Test2();
	result = mFunctor1(1, 9);
	//静态函数
	mFunctor1 = Test2::FunctorStatic;
	result = mFunctor1(1, 9);
	//函数模板
	mFunctor1 = FuncTemp<int>;
	result = mFunctor1(1, 6);
	//当做参数使用
	FuncCallBack([&](int a, int b)->int
		{
			return a + b;
		});



	//	bind
	//  延迟传参  1, 6
	auto FuncBind1 = bind(FunctorTest, 1, 6);
	result = FuncBind1();
	result = FuncBind1(9, 9);

	// placeholders::_1, placeholders::_2 占位
	auto FuncBind2 = bind(FunctorTest, placeholders::_1, placeholders::_2);
	//result = FuncBind2();   //err
	result = FuncBind2(9, 9);



	cout << " ------------------------- " << endl;


	struct FObject
	{
		int Init(int a, int b)
		{
			cout << "Init" << endl;
			return a + b;
		}
	}FObj;
	MObjectDelegate<FObject, int, int, int> ObjDelegate(&FObj, &FObject::Init);
	auto objresutl = ObjDelegate.Execute(10, 10);
	cout << "objresutl = " << objresutl << endl;

	MFuncDelegate<int, int, int>FunctionDelegate(FunctorTest);
	objresutl = FunctionDelegate.Execute(20, 60);
	cout << "objresutl = " << objresutl << endl;

	//单播代理
	FactoryDelegate<int, int, int> DelegateInstance;
	DelegateInstance.Bind(FunctorTest);
	objresutl = DelegateInstance.Execute(7, 9);
	cout << "objresutl = " << objresutl << endl;

	DelegateInstance.Bind(&FObj, &FObject::Init);
	objresutl = DelegateInstance.Execute(8, 9);
	cout << "objresutl = " << objresutl << endl;

	//创建代理
	auto DIn1 = FactoryDelegate<int, int, int>::Create(&FObj, &FObject::Init);
	DIn1.Execute(100, 100);

	auto DIn2 = FactoryDelegate<int, int, int>::Create(FunctorTest);
	DIn2.Execute(100, 1);

	auto DIn3 = FactoryDelegate<int, int, int>::Create([](int a, int b)->int
		{
			cout << " DIn3 " << endl;
			return a + b;
		});
	DIn3.Execute(99, 1);




	return 0;
}