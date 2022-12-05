/*
	��Ԫ�ࡢ��Ԫ����
*/

#include <stdio.h>
class TestClass {
	friend class Test2; //Test2����Է��ʱ����������Ϣ
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
		// ������Ԫ�����˽�к���
		testClass.TestFun1();
		testClass.TestFun2();
	}

private:
	TestClass testClass;
};


class Test3 {
public:
	/// <summary>
	/// ��Ԫ������û��thisָ�� �� ���Է��ʸ�������г�Ա��
	///		����ʹ��const�����ܱ��̳С�һ�����������Ƕ�������Ԫ����
	/// 
	///		����˳��������Ч�ʣ�����һ�����ţ����˹���˽����Щ�жϣ�ֱ�ӷ��ʣ����ڲ���Ա�����ٶ�һ�£�
	///		�ƻ�����ķ�װ��������
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