/*
	·为什么要引入模板：减少重复代码
	·编译器会按模板类型自动生成对应类型的代码
	·类模板匹配
	·什么是hpp文件
	·模板继承
	·模板使用多态
	·高级宏替换和类模板连用
	·单例模板
	·网络协议模板基础框架

	·遍历任意参（展开方式和递归方式）
	·获取可变参数的数量
	·什么是模板泛化：当前所有模板参数都未定义，只有等到使用的时候知道
	·什么是模板全特化：给定一个确定的类型，前提是要有个泛化的模板
	·通过模板偏特化来获取可变参数的字节大小
	·通过模板循环继承方式展开可变参数
	·通过using循环命名的方式展开可变参数
	·通过模板求最大整数
	·通过模板求内存对齐

	·通过工厂来构建任意参数对象
	·支持任意参数的简单代理

	·模板元编程
	·左值和右值（以等号作为判断，=的左边和右边）
	·左值引用（不能做带有表达式的操作） 右值引用（不能直接引用  一般用在临时变量的地方）
	·表达式不能是左值
	·常量不能做左值

	·std::integral_constant 定义预编译期的常量
*/

#include <iostream>
#include <type_traits> //模板元编程库
#include <vector>

#include "TempTest.h"
#include "SingletonPattern.h"
#include "NetProtocol.h"
#include "TemplateElement.h"


using namespace std;


template<class T>
class MVector
{
public:
	const T *operator[](int index) const {
		return &Data[index];
	}

	int Num() const
	{
		return 0;
	}

public:	//模板里面套模板
	template<typename T2>
	void Func()
	{
		T2 a;
	}


private:
	T *Data;

};

class TestA
{

};

//  template<typename T>  =  template<class T>
template<typename T>
void Printf_Arr(const MVector<T> &iarr)
{
	for (unsigned int i = 0; i < iarr.Num(); i++)
	{
		const T *ptr = iarr[i];
	}
}


struct MyStructTest
{
	void MyStructTestAA()
	{

	}

	virtual void MyStructTestBB()
	{

	}
};

struct MyStructTest2
{
	void MyStructTestAA()
	{

	}

	virtual void MyStructTestBB() = 0;

};

enum MyEnumTest
{

};



// T只允许数值类型 
template<class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type Func_Enableif_Test(T f)
{
	return f;
}

// T只允许非数值类型 
template<class T>
typename std::enable_if<!std::is_arithmetic<T>::value, T>::type Func_Enableif_Test(T f)
{
	return f;
}



int main()
{
	MVector<int> mv_i;
	MVector<float> mv_f;
	MVector<TestA *> mv_ta;

	mv_i.Func<int>();

	Printf_Arr<int>(mv_i);
	Printf_Arr(mv_i);  //如果参数里已经有一个模板T了，那么就可以省略调函数的T，编辑器可以自动匹配

	TempTest<int> tempT;
	tempT.Func2<TestAA>();
	TempTest<TestAA> tempAA;

	//类模板匹配
	TempTest<TestAA> tempAA2;
	tempAA2.Func3<float>();


	TempTestE testE;
	TempTestG testG;


	TempTestI testI;
	TempTestH<int> *Hptr = &testI; //模板指针
	Hptr->Init();
	Hptr->Destroy();
	Hptr->Func(1, 6);
	Hptr->Func(1);




	FMyClass<int> fmc;
	fmc.Work();
	FMyClassTwo<float> fmct;
	fmct.Work();
	FMyClassThree<int> fmcth;
	fmcth.Work();




	MThreadTest *tttest = TTTest::Get();
	tttest->Func();

	MThreadTest_Two *Test_Two = Two::Get();
	Test_Two->Func();
	MThreadTest_Three *Test_Three = Three::Get();
	Test_Three->Func();




	// 客户端
	int sa = 0;
	float sf = 1.0;
	char sc;
	NetControlMessage<NMT_Enter>::Send(sa, sf, sc);
	NetControlMessage<NMT_Login>::Send(sa, sc);
	//服务端
	NetControlMessage<NMT_Enter>::Receive(sa, sf, sc);




	int par1 = 10;
	float par2 = 11.5;
	char par3[] = "Hello";
	FunTest(par1, par2, par3);
	FunTest2(par1, par2, par3);
	FunTestLen(par1, par2, par3);




	int value1 = 1;
	int value2 = 66;
	int value3 = 3;
	int value4 = 99;
	int value = FuncValue(value1, value2, value3, value4);
	cout << value << endl;



	//TempTestLen<int, int, int, int> TempTestLen;
	//cout << TempTestLen.Num << endl;
	TEMP_TEST_LEN(TempTestLen, int, int, int, int);
	cout << TempTestLen.Num << endl;




	using Int_Alias = int;
	cout << "类型 = " << typeid(Int_Alias).name() << endl;
	//using SpawnIndex_Alias = SpawnIndex<10>::MType;
	//cout << typeid(SpawnIndex_Alias).name() << endl;
	using SpawnIndex_Alias = SpawnIndex<3>::MType;
	cout << typeid(SpawnIndex_Alias).name() << endl;	//struct HelloIndex<0,1,2>
	//SpawnIndex<3>::MType;
	//struct SpawnIndex :SpawnIndex<2, 2>
	//struct SpawnIndex<2, 2> :SpawnIndex<1, 1, 2>
	//struct SpawnIndex<1, 1, 2> :SpawnIndex<0, 0, 1, 2>
	//struct HelloIndex<0,1,2>



	using SpawnIndex_Alias_Two = SpawnIndex_Two<3>::MType_Two;
	cout << "using：" << typeid(SpawnIndex_Alias_Two).name() << endl;




	SpawnIndex<3>::MType *CreateTest1 = CreateObject_NoParam<SpawnIndex<3>::MType>();
	if (CreateTest1)
	{
		cout << "CreateTest1" << endl;
		delete CreateTest1;
		CreateTest1 = nullptr;
	}
	COTestA *cota = CreateObject<COTestA>();
	if (cota)
	{
		cout << "COTestA" << endl;
		delete cota;
		cota = nullptr;
	}
	COTestB *cotb = CreateObject<COTestB>(1, 2);
	if (cotb)
	{
		cout << "COTestB" << endl;
		delete cotb;
		cotb = nullptr;
	}




	COTestC *cotc = CreateObject<COTestC>();
	auto newFunc = CreateMDelegate(cotc, &COTestC::Print);
	newFunc(1, 9);




	int consti = ConstTest<int, 99999>::value;
	cout << "ConstTest" << consti << endl;

	RemoveConst<const int>::Type remConst1;
	remConst1 = 10;

	bool issame1 = isSame<int, int>::value;
	cout << "isSame 是否是同类型：" << (issame1 ? "True" : "False") << endl;
	issame1 = isSame<int, float>::value;
	cout << "isSame 是否是同类型：" << (issame1 ? "True" : "False") << endl;





	cout << "是否是同类型：" << is_same<int, float>::value << endl;
	cout << "TestA 是否是类或结构体：" << is_class<TestA>::value << endl;
	cout << "MyStructTest 是否是类或结构体：" << is_class<MyStructTest>::value << endl;
	cout << "int 是否是类或结构体：" << is_class<int>::value << endl;
	cout << "MyEnumTest 是否是枚举：" << is_enum<MyEnumTest>::value << endl;
	cout << "是否是整形：" << is_integral<int>::value << endl;
	cout << "是否是float：" << is_floating_point<float>::value << endl;
	cout << "是否是指针：" << is_pointer<float *>::value << endl;
	cout << "是否是左值：" << is_lvalue_reference<float &>::value << endl;
	cout << "是否是右值：" << is_rvalue_reference<float &&>::value << endl;
	cout << "是否是函数：" << is_function<float>::value << endl;
	cout << "是否是函数：" << is_function<void(int, int)>::value << endl;
	cout << "是否是函数：" << is_function<void(...)>::value << endl;
	cout << "是否是成员函数：" << is_member_function_pointer<int(MyStructTest:: *)()>::value << endl;
	cout << "是否是成员指针：" << is_member_object_pointer<int(MyStructTest:: *)>::value << endl;
	cout << "是否是数组：" << is_array<int[]>::value << endl;
	cout << "是否是数组：" << is_array<vector<int>>::value << endl;
	cout << "是否是整形或浮点型：" << is_arithmetic<int>::value << endl;
	cout << "是否是整形或浮点型：" << is_arithmetic<float>::value << endl;
	cout << "是否是抽象类：" << is_abstract<MyStructTest>::value << endl;
	cout << "是否是抽象类：" << is_abstract<MyStructTest2>::value << endl;
	cout << is_same<int &, int>::value << endl;
	cout << is_same<int &, add_lvalue_reference<int>::type>::value << endl; //add_lvalue_reference 添加引用
	cout << is_same<int, const int>::value << endl;
	cout << is_same<int, remove_const<const int>::type>::value << endl;

	conditional<true, int, float>::type conditionalTest = 100; // 第一个参数是true，那么conditionalTest的类型就是int，否则为false

	decay<int &>::type A1;	//int
	decay<int &&>::type A2; //int
	decay<const int>::type A3; //int
	decay<int[100]>::type A4; //int*
	decay<int(int)>::type A5;	//int(*)(int)



	// 限定模板类型为数字
	auto enableifTest = Func_Enableif_Test(1);
	TempTestE testEE;
	auto enableifTest2 = Func_Enableif_Test(testEE);




	//左值和右值（以等号作为判断，=的左边和右边）
	int iaa = 0, ibb = 1;
	iaa = ibb + 1;	//iaa是左值，ibb是右值

	// 表达式不能是左值
	// err (iaa + ibb) = iaa + 1; iaa++ = ibb + 1;

	// 常量不能做左值
	// 100 = 1;

	// 左值引用和右值引用
	int &lefeA = iaa;			//左值引用  不能做带有表达式的操作  
	int &&rightB = ibb + 100;	//右值引用  不能直接引用  一般用在临时变量的地方

	cout << lefeA << " ----  " << rightB << endl;




	typedef std::integral_constant<int, 100>::type CompileConstTest;
	CompileConstTest cct;
	int iaaa = cct;
	int iaaaa = static_cast<int>(cct);
	int iaaaaa = cct.operator CompileConstTest::value_type();
	cout << iaaa << " ----  " << iaaaa << " ----  " << iaaaaa << " ----  " << endl;



	cout << IntMax<1, 6, 66, 7, 89, 5454, 55, 10000001>::value << endl;




	struct MyStructAA
	{
		int a;
		int b;
		double dd;
		float cc;
	};

	int neicunduiqi = alignof(MyStructAA);
	cout << "内存对齐1：" << neicunduiqi << endl;
	cout << "内存对齐2：" << MaxAlign<char, int, float, long, long long>::value << endl;


	return 0;
}