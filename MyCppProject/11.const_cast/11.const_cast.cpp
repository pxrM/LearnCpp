/*
	·const_cast
	·reinterpret_cast
	·dynamic_cast
	·static_cast
	·const
	·函数返回对象一般用指针
*/

#include <iostream>

using namespace std;


class TestA
{
public:
	TestA()
	{

	}

	void Init()
	{
		printf("Init\n");
	}

	void Init_1() const //这里的const表示函数内部不能修改类成员
	{
		//a = 0;	//error C3490: 由于正在通过常量对象访问“a”，因此无法对其进行修改
		printf("Init_1\n");
	}

	virtual void On() {

	}

public:
	int a;
	int b;
	int c;

};

class TestB :public TestA
{
public:
	TestB()
	{

	}

	void TestXX()
	{
		printf("TestB \n");
	}

	virtual void On() override
	{

	}


};

class TestC {
public:
	int a;
	int b;
	int c;
};

class TestD :public TestC {

};



// 参数a不能被修改 tc指针所指向对象的内容是不能被修改的
void Func1(const int a, const TestC *tc)
{
	//a = 10;		err
	//tc->a = 10;	err
	tc = new TestC(); //转移指针所指向的地址
	//tc->a = 10;	err

	const TestD *testD1 = new TestD();
	//testD1->a = 0;	err 指针所指向的对象的成员不能被修改
	testD1 = new TestD(); //可以修改指针所指向的地址，但是地址的值依然不能修改
	//testD1->a = 0;	err

	const TestD *const testD2 = new TestD(); //指针对象的值 和 指向对象的值 都不能被修改
	//testD1->a = 0;	err
	//testD2 = new TestD();		err
}

// 返回的int值不能被修改
const int GetID()
{
	return 0;
}

class TestE
{
public:
	int a;
public:
	// 类成员不能被修改
	void Func() const
	{
		//a = 0;
	}
};



int main()
{
	const TestA *ta = new TestA();
	//ta->Init();	//error C2662: “void TestA::Init(void)”: 不能将“this”指针从“const TestA”转换为“TestA &”
	ta->Init_1();
	// const_cast 去掉ta的const
	TestA *ta2 = const_cast<TestA *>(ta);
	ta2->Init();

	//c风格强转，没有安全监测，结果都会转为一个指针，会出现野指针
	TestA *testC = (TestA *)(ta);
	testC->Init();


	// reinterpret_cast 可以将类型转为指针，将指针转为类型
	int a1 = reinterpret_cast<int>(testC);
	TestA *a2 = reinterpret_cast<TestA *>(a1);
	int *a3 = reinterpret_cast<int *>(testC);
	TestA *a4 = reinterpret_cast<TestA *>(a3);
	a2->Init();


	// dynamic_cast 动态转换（向上或者向下转换）主要用在类之间，转换时会进行类型检测，如果无法通过会返回一个NULL，转换的类必须要有至少一个虚函数
	// 向下转换
	TestA *tab = new TestB();
	TestB *tb = dynamic_cast<TestB *>(tab);
	// 向上转换
	TestA *ta222 = dynamic_cast<TestA *>(tb);

	// static_const 静态转换（向上或者向下转换） 不安全
	TestC *tc = new TestC();
	TestD *td = static_cast<TestD *>(tc);


	delete ta;
	delete tab;
	delete td;

	return 0;
}