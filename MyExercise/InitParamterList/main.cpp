/*
	当一个类中组合了其它的类对象作为成员时，拷贝构造函数也必须使用初始化参数列表，来构造对象成员然后拷贝	
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
		cout << "构造小A2" << endl;
	}
	A2(int a, string str)
	{
		this->a = a;
		this->str = str;
		cout << "构造大A2" << endl;
	}
	~A2()
	{
		cout << "析构A2" << endl;
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
		cout << "构造B2" << endl;
	}
	~B2()
	{
		cout << "析构B2" << endl;
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
	*	error C2512: “A”: 没有合适的默认构造函数可用
	*	这个问题在于，在B类中组合了一个A类的成员，B类在构造对象时，同时会构造一个A类作为B类的成员，
	*   但是因为A类自定义了一个有参的构造函数，所以在构造A类时，编译器不会使用默认构造函数，而是使用自定义的有参构造函数，
	*	问题就出在这里，编译器在构造A类时，没有参数传递到A类的有参构造函数。
	* 
	*	初始化列表就是用来解决这种问题的，初始化参数列表可以让我们在构造B类对象时，根据参数列表来构造不同的A类成员。
	*/
	//B b(1);

	test();
	return 0;
}
