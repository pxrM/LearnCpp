#pragma once
#include <iostream>

using namespace std;

class TestAA
{
public:
	bool Work()
	{
		printf("Work \n");
		return false;
	}
};

template<typename T>
class TempTest
{
public:
	void Func1();

	template<typename T1>
	T1 *Func2()
	{
		printf("Func2  ");
		T1 t2;
		bool bw = t2.Work();

		return nullptr;
	}

	template<typename T1>
	T1 *Func3()
	{
		printf("Func3  ");
		T t3;
		bool bw = t3.Work();

		return nullptr;
	}

private:
	T *Data;
};




///////////////////////////// 模板继承 /////////////////////////////

class TempTestA
{
public:
	bool TempTestWork();
};

class TempTestB :public TempTest<TempTestA>
{

};

template<typename T>
class TempTestC :public TempTest<T>
{

};

template<typename T1, typename T2, typename T3>
class TempTestD :public TempTest<T1>
{
public:
	T2 Data2;
	T1 Data3;
};


////////////////////// 模板虚继承 //////////////////////
class TempTestE :virtual public TempTest<TempTestA>
{
	typedef TempTest<TempTestA> Super;

public:
	TempTestE()
		:Super()
	{

	}
};

class TempTestF :virtual public TempTest<TempTestA>
{
	typedef TempTest<TempTestA> Super;

public:
	TempTestF()
		:Super()
	{

	}
};

class TempTestG : public TempTestE, public TempTestF
{
public:
};
///////////////////////////////////////////////////////


////////////////////// 模板使用多态 //////////////////////
template<typename T>
class TempTestH
{
public:
	virtual void Init()
	{
		cout << "H::Init" << endl;
	}
	virtual void Destroy()
	{
		cout << "H::Destroy" << endl;
	}

	void Func()
	{
		cout << "H::Func" << endl;
	}
	void Func(int a, int b)
	{
		cout << "H::Func(int a, int b)" << endl;
	}
	void Func(...)
	{
		cout << "H::Func(...)" << endl;
	}

private:
	T *Data;

};

class TempTestI :public TempTestH<int>
{
	typedef TempTestH<int> Super;
public:
	virtual void Init() override {
		cout << "I::Init" << endl;
	}
	virtual void Destroy() override {
		Super::Destroy();
		cout << "I::Destroy" << endl;
	}
};

///////////////////////////////////////////////////////


////////////////////// 高级宏替换 //////////////////////
#define HELLO_CLASS(ClassName, Code)\
template<class T> \
class F##ClassName \
{ \
public: \
	void Work() \
	{ \
		Code; \
	} \
private: \
	T *Data; \
};
// 使用
HELLO_CLASS(MyClass, cout << "MyClass" << endl;)
HELLO_CLASS(MyClassTwo, {
	cout << "666666666666666" << endl;
	cout << "MyClassTwo" << endl;
	})

// 带任意参
#define HELLO_CLASS_PARAM(ClassName, Code, Str, ...) \
template<class T> \
class F##ClassName \
{ \
public: \
	void Work() \
	{ \
		Code; \
		printf(#Str, __VA_ARGS__); \
	} \
};
HELLO_CLASS_PARAM(MyClassThree, { cout << "MyClassThree" << endl; }, "%s 任意参", "----------")
///////////////////////////////////////////////////////