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
*/

#include <iostream>
#include "TempTest.h"
#include "SingletonPattern.h"
#include "NetProtocol.h"

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

	return 0;
}