/*
	友元类、友元函数
*/

#include <stdio.h>
class TestClass {
	friend class Test2; //Test2类可以访问本类的所有信息
public:
	void TestFun(){}

private:
	void TestFun1() {}
	void TestFun2() {}
	void TestFun3() {}

protected:
	void TestFun4(){}
};


class Test2 {
public:
	void Init() {
		testClass.TestFun();
		// 利用友元类访问私有函数
		testClass.TestFun1();
		testClass.TestFun2();
	}

private:
	TestClass testClass;
};


class Test3 {
public:
	/// <summary>
	/// 友元函数（没有this指针 ） 可以访问该类的所有成员，
	///		不能使用const、不能被继承、一个函数可以是多个类的友元函数
	/// 
	///		提高了程序的运行效率（开了一个后门，少了共有私有这些判断，直接访问，和内部成员访问速度一致）
	///		破坏了类的封装和隐蔽性
	/// </summary>
	/// <param name="t3"></param>
	friend void Printf_F(Test3& t3) /*const*/ {
		t3.Print();
		printf("%d \n", t3.b);
		printf("%d \n", t3.a);
	}

	static void Printf_S(Test3& t3) {
		t3.Print();
		printf("%d \n", t3.b);
		printf("%d \n", t3.a);
	}

private:
	void Print() {
		a = 0;
		b = 10;
	}

private:
	int a;
	int b;
};



int main() {
	Test2 test2;
	test2.Init();


	Test3 t3;
	Printf_F(t3);
	Test3::Printf_S(t3);

	return 0;
}