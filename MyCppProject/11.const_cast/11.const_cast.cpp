/*
	��const_cast
	��reinterpret_cast
	��dynamic_cast
	��static_cast
	��const
	���������ض���һ����ָ��
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

	void Init_1() const //�����const��ʾ�����ڲ������޸����Ա
	{
		//a = 0;	//error C3490: ��������ͨ������������ʡ�a��������޷���������޸�
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



// ����a���ܱ��޸� tcָ����ָ�����������ǲ��ܱ��޸ĵ�
void Func1(const int a, const TestC *tc)
{
	//a = 10;		err
	//tc->a = 10;	err
	tc = new TestC(); //ת��ָ����ָ��ĵ�ַ
	//tc->a = 10;	err

	const TestD *testD1 = new TestD();
	//testD1->a = 0;	err ָ����ָ��Ķ���ĳ�Ա���ܱ��޸�
	testD1 = new TestD(); //�����޸�ָ����ָ��ĵ�ַ�����ǵ�ַ��ֵ��Ȼ�����޸�
	//testD1->a = 0;	err

	const TestD *const testD2 = new TestD(); //ָ������ֵ �� ָ������ֵ �����ܱ��޸�
	//testD1->a = 0;	err
	//testD2 = new TestD();		err
}

// ���ص�intֵ���ܱ��޸�
const int GetID()
{
	return 0;
}

class TestE
{
public:
	int a;
public:
	// ���Ա���ܱ��޸�
	void Func() const
	{
		//a = 0;
	}
};



int main()
{
	const TestA *ta = new TestA();
	//ta->Init();	//error C2662: ��void TestA::Init(void)��: ���ܽ���this��ָ��ӡ�const TestA��ת��Ϊ��TestA &��
	ta->Init_1();
	// const_cast ȥ��ta��const
	TestA *ta2 = const_cast<TestA *>(ta);
	ta2->Init();

	//c���ǿת��û�а�ȫ��⣬�������תΪһ��ָ�룬�����Ұָ��
	TestA *testC = (TestA *)(ta);
	testC->Init();


	// reinterpret_cast ���Խ�����תΪָ�룬��ָ��תΪ����
	int a1 = reinterpret_cast<int>(testC);
	TestA *a2 = reinterpret_cast<TestA *>(a1);
	int *a3 = reinterpret_cast<int *>(testC);
	TestA *a4 = reinterpret_cast<TestA *>(a3);
	a2->Init();


	// dynamic_cast ��̬ת�������ϻ�������ת������Ҫ������֮�䣬ת��ʱ��������ͼ�⣬����޷�ͨ���᷵��һ��NULL��ת���������Ҫ������һ���麯��
	// ����ת��
	TestA *tab = new TestB();
	TestB *tb = dynamic_cast<TestB *>(tab);
	// ����ת��
	TestA *ta222 = dynamic_cast<TestA *>(tb);

	// static_const ��̬ת�������ϻ�������ת���� ����ȫ
	TestC *tc = new TestC();
	TestD *td = static_cast<TestD *>(tc);


	delete ta;
	delete tab;
	delete td;

	return 0;
}