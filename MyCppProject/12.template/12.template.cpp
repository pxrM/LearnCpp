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

	return 0;
}