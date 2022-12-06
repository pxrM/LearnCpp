/*
	·类构造函数和析构函数
	·初始化列表
	·this指针
	·拷贝构造函数--深拷贝和浅拷贝
	·namespace
*/

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////

class Test {

};

class TestSuper {

};

class Test1 :public TestSuper {
public:
	Test1();
	Test1(int ia, int ib, int ic);
	Test1(const Test1 &test);
	~Test1();

public:
	int a;
	int b;
	int c;

	Test *test;
};

Test1::Test1()
{
	a = 10;
	b = 16;
	c = 6;

	test = new Test();
}

//初始化列表，调用时机要比上面的方式要快，要按照当前变量声明的顺序
Test1::Test1(int ia, int ib, int ic)
	:a(ia)
	, b(ib)
	, c(ic)
{

	test = new Test();
}

Test1::Test1(const Test1 &test)
{
	this->a = test.a;
	this->b = test.b;
	this->c = test.c;
	this->test = new Test();
	*this->test = *test.test; //需要保证Test类里都是值，如果有指针的话需要重写深拷贝
}

////初始化列表
//Test1::Test1(int ia, int ib, int ic)
//	:TestSuper()//调用父类的构造
//	, a(ia)
//	, b(ib)
//	, c(ic)
//{
//
//	test = new Test();
//}

Test1::~Test1()
{
	if (test)
	{
		delete test;
		test = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////

const Test1 *thisPtr = nullptr; //每个类内部都会有这样的一个this指针

//////////////////////////////////////////////////////////////////////////////////////

namespace AssetHello
{
	enum EHello
	{
		EA,
		EB,
	};

	struct SHello
	{
		void Init() {}
		void Str() {}
	};

	class IInterface
	{

	};

	class CHello :public IInterface
	{

	};

	//定义函数体
	void AssetHelloFunc() {}
	CHello *GetHello();
}

namespace AssetHello
{
	CHello *GetHello()
	{
		return nullptr;
	}
}


//////////////////////////////////////////////////////////////////////////////////////


int main()
{
	{
		Test1 t1; //默认走Test1();
		std::cout << t1.a << "   " << t1.b << "   " << t1.c << std::endl;

		Test1 t2(99, 100, 1); //走Test1(int ia, int ib, int ic)
		std::cout << t2.a << "   " << t2.b << "   " << t2.c << std::endl;

		Test1 t3{ 7,0,1 }; //初始化列表
		std::cout << t3.a << "   " << t3.b << "   " << t3.c << std::endl;

		//拷贝
		Test1 A;
		std::cout << A.a << "   " << A.b << "   " << A.c << std::endl;
		Test1 B(1, 2, 3);
		//A = B; //需要重载算术运算符
		Test1 C(B);//浅拷贝（内存对齐，只拷贝了内存地址，而不是值）
		std::cout << B.a << "   " << B.b << "   " << B.c << std::endl;
		std::cout << C.a << "   " << C.b << "   " << C.c << std::endl;

	}

	{
		AssetHello::EA;
		AssetHello::EHello::EA;

		AssetHello::CHello *hPtr = new AssetHello::CHello();
		AssetHello::GetHello();

		using namespace AssetHello;
		AssetHelloFunc();
	}

	return 0;
}

