/*
	��ΪʲôҪ����ģ�壺�����ظ�����
	���������ᰴģ�������Զ����ɶ�Ӧ���͵Ĵ���
	����ģ��ƥ��
	��ʲô��hpp�ļ�
	��ģ��̳�
	��ģ��ʹ�ö�̬
	���߼����滻����ģ������
	������ģ��
	������Э��ģ��������

	����������Σ�չ����ʽ�͵ݹ鷽ʽ��
	����ȡ�ɱ����������
	��ʲô��ģ�巺������ǰ����ģ�������δ���壬ֻ�еȵ�ʹ�õ�ʱ��֪��
	��ʲô��ģ��ȫ�ػ�������һ��ȷ�������ͣ�ǰ����Ҫ�и�������ģ��
	��ͨ��ģ��ƫ�ػ�����ȡ�ɱ�������ֽڴ�С
	��ͨ��ģ��ѭ���̳з�ʽչ���ɱ����
	��ͨ��usingѭ�������ķ�ʽչ���ɱ����
	��ͨ��ģ�����������
	��ͨ��ģ�����ڴ����

	��ͨ�����������������������
	��֧����������ļ򵥴���

	��ģ��Ԫ���
	����ֵ����ֵ���ԵȺ���Ϊ�жϣ�=����ߺ��ұߣ�
	����ֵ���ã����������б��ʽ�Ĳ����� ��ֵ���ã�����ֱ������  һ��������ʱ�����ĵط���
	�����ʽ��������ֵ
	��������������ֵ

	��std::integral_constant ����Ԥ�����ڵĳ���
*/

#include <iostream>
#include <type_traits> //ģ��Ԫ��̿�
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

public:	//ģ��������ģ��
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



// Tֻ������ֵ���� 
template<class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type Func_Enableif_Test(T f)
{
	return f;
}

// Tֻ�������ֵ���� 
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
	Printf_Arr(mv_i);  //����������Ѿ���һ��ģ��T�ˣ���ô�Ϳ���ʡ�Ե�������T���༭�������Զ�ƥ��

	TempTest<int> tempT;
	tempT.Func2<TestAA>();
	TempTest<TestAA> tempAA;

	//��ģ��ƥ��
	TempTest<TestAA> tempAA2;
	tempAA2.Func3<float>();


	TempTestE testE;
	TempTestG testG;


	TempTestI testI;
	TempTestH<int> *Hptr = &testI; //ģ��ָ��
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




	// �ͻ���
	int sa = 0;
	float sf = 1.0;
	char sc;
	NetControlMessage<NMT_Enter>::Send(sa, sf, sc);
	NetControlMessage<NMT_Login>::Send(sa, sc);
	//�����
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
	cout << "���� = " << typeid(Int_Alias).name() << endl;
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
	cout << "using��" << typeid(SpawnIndex_Alias_Two).name() << endl;




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
	cout << "isSame �Ƿ���ͬ���ͣ�" << (issame1 ? "True" : "False") << endl;
	issame1 = isSame<int, float>::value;
	cout << "isSame �Ƿ���ͬ���ͣ�" << (issame1 ? "True" : "False") << endl;





	cout << "�Ƿ���ͬ���ͣ�" << is_same<int, float>::value << endl;
	cout << "TestA �Ƿ������ṹ�壺" << is_class<TestA>::value << endl;
	cout << "MyStructTest �Ƿ������ṹ�壺" << is_class<MyStructTest>::value << endl;
	cout << "int �Ƿ������ṹ�壺" << is_class<int>::value << endl;
	cout << "MyEnumTest �Ƿ���ö�٣�" << is_enum<MyEnumTest>::value << endl;
	cout << "�Ƿ������Σ�" << is_integral<int>::value << endl;
	cout << "�Ƿ���float��" << is_floating_point<float>::value << endl;
	cout << "�Ƿ���ָ�룺" << is_pointer<float *>::value << endl;
	cout << "�Ƿ�����ֵ��" << is_lvalue_reference<float &>::value << endl;
	cout << "�Ƿ�����ֵ��" << is_rvalue_reference<float &&>::value << endl;
	cout << "�Ƿ��Ǻ�����" << is_function<float>::value << endl;
	cout << "�Ƿ��Ǻ�����" << is_function<void(int, int)>::value << endl;
	cout << "�Ƿ��Ǻ�����" << is_function<void(...)>::value << endl;
	cout << "�Ƿ��ǳ�Ա������" << is_member_function_pointer<int(MyStructTest:: *)()>::value << endl;
	cout << "�Ƿ��ǳ�Աָ�룺" << is_member_object_pointer<int(MyStructTest:: *)>::value << endl;
	cout << "�Ƿ������飺" << is_array<int[]>::value << endl;
	cout << "�Ƿ������飺" << is_array<vector<int>>::value << endl;
	cout << "�Ƿ������λ򸡵��ͣ�" << is_arithmetic<int>::value << endl;
	cout << "�Ƿ������λ򸡵��ͣ�" << is_arithmetic<float>::value << endl;
	cout << "�Ƿ��ǳ����ࣺ" << is_abstract<MyStructTest>::value << endl;
	cout << "�Ƿ��ǳ����ࣺ" << is_abstract<MyStructTest2>::value << endl;
	cout << is_same<int &, int>::value << endl;
	cout << is_same<int &, add_lvalue_reference<int>::type>::value << endl; //add_lvalue_reference �������
	cout << is_same<int, const int>::value << endl;
	cout << is_same<int, remove_const<const int>::type>::value << endl;

	conditional<true, int, float>::type conditionalTest = 100; // ��һ��������true����ôconditionalTest�����;���int������Ϊfalse

	decay<int &>::type A1;	//int
	decay<int &&>::type A2; //int
	decay<const int>::type A3; //int
	decay<int[100]>::type A4; //int*
	decay<int(int)>::type A5;	//int(*)(int)



	// �޶�ģ������Ϊ����
	auto enableifTest = Func_Enableif_Test(1);
	TempTestE testEE;
	auto enableifTest2 = Func_Enableif_Test(testEE);




	//��ֵ����ֵ���ԵȺ���Ϊ�жϣ�=����ߺ��ұߣ�
	int iaa = 0, ibb = 1;
	iaa = ibb + 1;	//iaa����ֵ��ibb����ֵ

	// ���ʽ��������ֵ
	// err (iaa + ibb) = iaa + 1; iaa++ = ibb + 1;

	// ������������ֵ
	// 100 = 1;

	// ��ֵ���ú���ֵ����
	int &lefeA = iaa;			//��ֵ����  ���������б��ʽ�Ĳ���  
	int &&rightB = ibb + 100;	//��ֵ����  ����ֱ������  һ��������ʱ�����ĵط�

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
	cout << "�ڴ����1��" << neicunduiqi << endl;
	cout << "�ڴ����2��" << MaxAlign<char, int, float, long, long long>::value << endl;


	return 0;
}