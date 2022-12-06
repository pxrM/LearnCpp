/*
	���๹�캯������������
	����ʼ���б�
	��thisָ��
	���������캯��--�����ǳ����
	��namespace
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

//��ʼ���б�����ʱ��Ҫ������ķ�ʽҪ�죬Ҫ���յ�ǰ����������˳��
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
	*this->test = *test.test; //��Ҫ��֤Test���ﶼ��ֵ�������ָ��Ļ���Ҫ��д���
}

////��ʼ���б�
//Test1::Test1(int ia, int ib, int ic)
//	:TestSuper()//���ø���Ĺ���
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

const Test1 *thisPtr = nullptr; //ÿ�����ڲ�������������һ��thisָ��

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

	//���庯����
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
		Test1 t1; //Ĭ����Test1();
		std::cout << t1.a << "   " << t1.b << "   " << t1.c << std::endl;

		Test1 t2(99, 100, 1); //��Test1(int ia, int ib, int ic)
		std::cout << t2.a << "   " << t2.b << "   " << t2.c << std::endl;

		Test1 t3{ 7,0,1 }; //��ʼ���б�
		std::cout << t3.a << "   " << t3.b << "   " << t3.c << std::endl;

		//����
		Test1 A;
		std::cout << A.a << "   " << A.b << "   " << A.c << std::endl;
		Test1 B(1, 2, 3);
		//A = B; //��Ҫ�������������
		Test1 C(B);//ǳ�������ڴ���룬ֻ�������ڴ��ַ��������ֵ��
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

