/*
	��һ������������������������Ϊ��Աʱ���������캯��Ҳ����ʹ�ó�ʼ�������б�����������ԱȻ�󿽱�	
*/


#include <iostream>

using namespace std;

/*
class A
{
public:
	A(int a)
	{
		this->a = a;
	}
private:
	int a;
};

class B
{
public:
	B(int i)
	{
		this->i = i;
	}
	int i;
	A a;

};*/



class A2
{
public:
	A2(int a)
	{
		this->a = a;
		cout << "����СA2" << endl;
	}
	A2(int a, string str)
	{
		this->a = a;
		this->str = str;
		cout << "�����A2" << endl;
	}
	~A2()
	{
		cout << "����A2" << endl;
	}
	int a;
	string str;
};

class B2
{
public:
	B2(int i) :a1(1), a2(2, "asd")
	{
		this->i = i;
		cout << "����B2" << endl;
	}
	~B2()
	{
		cout << "����B2" << endl;
	}

	int i;
	A2 a1;
	A2 a2;
};
void test()
{
	B2 b(1);
	cout << b.a1.str << endl;
	cout << b.a2.str << endl;
}



int main()
{
	/*
	*	error C2512: ��A��: û�к��ʵ�Ĭ�Ϲ��캯������
	*	����������ڣ���B���������һ��A��ĳ�Ա��B���ڹ������ʱ��ͬʱ�ṹ��һ��A����ΪB��ĳ�Ա��
	*   ������ΪA���Զ�����һ���вεĹ��캯���������ڹ���A��ʱ������������ʹ��Ĭ�Ϲ��캯��������ʹ���Զ�����вι��캯����
	*	����ͳ�������������ڹ���A��ʱ��û�в������ݵ�A����вι��캯����
	* 
	*	��ʼ���б�������������������ģ���ʼ�������б�����������ڹ���B�����ʱ�����ݲ����б������첻ͬ��A���Ա��
	*/
	//B b(1);

	test();
	return 0;
}
