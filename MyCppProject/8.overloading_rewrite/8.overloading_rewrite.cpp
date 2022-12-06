/*
	·重载	（c语言不支持重载(多态)）
	·重载在继承中的问题	（会访问子类中的函数而不会访问父类 例testb.FuncC()）
	·虚函数、虚函数表（在编译器前会加入到虚函数表中）
	·final的用法（需求背景：父类有些虚函数不希望子类去重写，但是它已经加了virtual关键字）
	·override	（主要起到检测作用，帮检查父类里这个函数是不是可以被重写）
*/

#include <iostream>

using namespace std;

/////////////////////// 函数重载 ///////////////////////
void Func(int a)
{

}

void Func(int a, int b)
{

}

void Func(string str)
{

}
/////////////////////// 函数重载 ///////////////////////

/////////////////////// 类重载&虚函数 ////////////////////////
class TestA
{
public:
	//成员变量（函数）
	void FuncC()
	{
		printf("TEST_A \n");
	}

	void FuncC(int a)
	{

	}

	void FuncC(int a, int b)
	{

	}

	void FuncC(string str)
	{

	}

public:
	//静态函数
	static void FuncS(int a)
	{

	}

	static void FuncS(int a, int b)
	{

	}

	static void FuncS(string str)
	{

	}

public:
	//虚函数（在编译器前会加入到虚函数表中，virtual关键字也是个指针会占四个字节）
	virtual void FuncV()
	{
		printf("A_FuncV \n");
	}

};


class TestB :public TestA
{
public:
	void FuncC()
	{
		printf("TEST_B \n");
	}

	virtual void FuncV() override
	{
		printf("B_FuncV \n");
	}
};



class IInterface
{
public:
	//纯虚函数（虚函数后面=0的都是纯虚函数，子类必须要重写）
	virtual void Init() = 0;
	virtual void Destroy() = 0;
};

class NewObject_Err : public IInterface
{

};

class NewObject : public IInterface
{
public:
	virtual void Init() final; //当前函数止于此类，其它类不能重写了
	virtual void Destroy();
};
void NewObject::Init()
{
}

void NewObject::Destroy()
{
}

class NewObject_Two : public NewObject
{
public:
	//virtual void Init(){}  //error C3248: “NewObject::Init”: 声明为“final”的函数无法被“NewObject_Two::Init”重写
	virtual void Destroy() {

	}
};

//作用类表示此类不能再被继承了
class NewObject_Three final :public IInterface
{

};

//class NewObject_Four :public NewObject_Three	// error C3246: “NewObject_Four”: 无法从“NewObject_Three”继承，因为它已被声明为“final”
//{
//
//};


/////////////////////// 类重载&虚函数 ///////////////////////

/////////////////////////////////////////////////////////////////////
class HelloA
{

};

class HelloB :public HelloA
{

};


class HelloC :public HelloA
{
public:
	int a;
};

class HelloD
{
public:
	void Init(){}
};

class HelloE
{
public:
	virtual void Init() {}
};

class HelloF
{
public:
	virtual void Init1() {}
	virtual void Init2() {}
	virtual void Init3() {}
};

/////////////////////////////////////////////////////////////////////



int main()
{
	Func(1);
	Func(1, 2);
	Func("ssss");

	TestA::FuncS(2);
	TestA::FuncS(2, 6);
	TestA::FuncS("999");

	TestA test;
	test.FuncC(1);
	test.FuncC(1, 8);
	test.FuncC("1111");

	printf("//////////////\n");

	TestB testb;
	testb.FuncC(); //走的子类，不会走父类
	printf("//////////////\n");
	testb.FuncV(); //走的子类重写
	TestA *ta = &testb; //普通函数如果将子类转为父类的话，那么执行的是父类里的，如果是virtual的话执行的是子类里的
	ta->FuncV(); //走的子类重写
	ta->FuncC(); //走的父类


	//NewObject_Err objE; //error C2259: “NewObject_Err”: 无法实例化抽象类
	NewObject obj;



	printf("//////////////\n");
	HelloA ah; // 如果没有成员的话会默认分配一个字节，起到占位的作用，让编译器知道这个类需要去内存分配的，如果有其它成员变量，就会把这个占位移除掉
	int len = sizeof(ah);
	cout << "ah大小 = " << len << "字节" << endl; //1

	HelloA ab;
	len = sizeof(ab);
	cout << "ab大小 = " << len << "字节" << endl; //1

	HelloC ac;
	len = sizeof(ac);
	cout << "ac大小 = " << len << "字节" << endl; //4

	HelloD ad;
	len = sizeof(ad);
	cout << "ad大小 = " << len << "字节" << endl; //1

	//////////////////////////////如果类里有virtual，会分配四个字节，这四个字节就是virtual指针，专门指向虚函数表
	HelloE ae;
	len = sizeof(ae);
	cout << "ae大小 = " << len << "字节" << endl; //4

	HelloF af;
	len = sizeof(af);
	cout << "af大小 = " << len << "字节" << endl; //4
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	return 0;
}


