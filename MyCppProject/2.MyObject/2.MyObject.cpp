#include <iostream>

using namespace std;

/*
	�ṹ��Ĭ�Ϸ���Ȩ����public
*/
struct StructTestSuper
{
protected:
	int m0;

};

struct StructTest :public StructTestSuper
{
	StructTest()
	{

	}
	~StructTest()
	{

	}


	int a;
	float b;
	void Func1(){}

private:
	int m1;
	void Func2() {}

protected:
	int m2;
	void Func3() {}

};


void GlobalFunc()
{

}

class Monster
{
public:
	Monster();
	~Monster();

private:

};

Monster::Monster()
{
	// ���ֵ���ȫ�ֺ����ķ�ʽ
	::GlobalFunc();
	GlobalFunc();
}

Monster::~Monster()
{
}

void main()
{
	StructTest test;
	test.a = 0;
	test.b = 0;
	//test.m1  �޷�����
}