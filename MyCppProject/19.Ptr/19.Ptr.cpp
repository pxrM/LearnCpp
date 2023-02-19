#include <iostream>
#include "MSharedPtr.h"


using namespace std;


//enable_shared_from_this  �����ڲ�����һ����ָ��	UE��TSharedFromThis
class CTestPtr :public enable_shared_from_this<CTestPtr>
{
public:
	CTestPtr()
	{
		a = 100000;
	}
	~CTestPtr()
	{

	}

	void Init()
	{
		cout << "init" << endl;
	}

private:
	int a;
};


class CTestPtr2
{
public:
	CTestPtr2()
	{
		a = 100000;
	}
	~CTestPtr2()
	{
	}

	void Init()
	{
		cout << "CTestPtr2 init" << endl;
	}

private:
	int a;
};


class IInterface
{
public:
	void SetPtr(shared_ptr<CTestPtr> InPtr)
	{
		CWeak = InPtr;
	}

	virtual void DoWork() = 0;

protected:
	weak_ptr<CTestPtr> CWeak;
};

class B :public IInterface
{
public:
	virtual void DoWork() override
	{
		CWeak.lock()->Init();
	}
};


class ATest
{
public:
	ATest()
		:CShared(new CTestPtr)
	{
	}

	IInterface* CreateInterface()
	{
		IInterface* face = new B();
		face->SetPtr(CShared);
		return face;
	}

	shared_ptr<CTestPtr> Get();

private:
	shared_ptr<CTestPtr> CShared;
};

shared_ptr<CTestPtr> ATest::Get()
{
	return CShared;
}



class TestDelete
{
	int count;

public:
	TestDelete()
		:count(0)
	{}

	template<class T>
	void operator()(T* p)
	{
		cout << "operator()" << endl;
		delete p;
	}
};



int main()
{
	// ��ָ��
	int* iPtr = new int;

	// ����ָ��	std::shared_ptr
	std::shared_ptr<int>  siPtr1(iPtr);
	std::shared_ptr<int> siPtr2 = std::make_shared<int>(12);	//����һ���ռ䣬����ֵ����Ϊ12
	std::shared_ptr<int> siPtr3(siPtr1);	//�������ü���	//���м��
	std::shared_ptr<int> siPtr4 = siPtr1;
	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;
	siPtr4 = nullptr;	//�������ü���	����������� ���Ǽ���Ϊ0��
	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;
	int* iPtr2 = siPtr1.get();	//תΪԭʼָ�루��ָ�룩
	int ivalue = *siPtr1;	//��ȡֵ
	bool bSingle = siPtr1.unique(); //�ǲ���Ψһ��
	//siPtr1.swap(siPtr2);	//����
	siPtr1.reset();	//reset = (siPtr1 = nullptr)

	shared_ptr<CTestPtr> ctsptr1(new CTestPtr);
	CTestPtr* ctptr = ctsptr1.get();	//ת��ָ��
	shared_ptr<CTestPtr> ctsptr2 = ctptr->shared_from_this();	//ת����ָ��

	// ��ָ�� std::weak_ptr		UE4��TWeakPtr
	std::weak_ptr<CTestPtr> swp1 = ctsptr2;
	swp1.lock()->Init();	//lock()ת��Ϊ����ָ�벢�������ü���
	if (swp1.use_count() == 0 || swp1.expired())
	{
		cout << "ʧЧ��" << endl;
	}



	ATest ATest1;
	IInterface* ii = ATest1.CreateInterface();
	ii->DoWork();

	/*
		std::auto_ptr<CTestPtr> c++11��׼�б�����
		std::auto_ptr_ref<CTestPtr>
		std::unique_ptr<CTestPtr>
	*/
	auto_ptr<CTestPtr> autop1(new CTestPtr());
	auto_ptr<CTestPtr> autop2;
	autop2 = autop1;	//autop1=null �����autop1�Ŀ���Ȩ�����׵����ڴ汼��
	CTestPtr* cc1 = autop2.release();
	autop2.reset(new CTestPtr());	//��������һ����
	CTestPtr* cc2 = autop2.get();

	unique_ptr<CTestPtr> autop3(new CTestPtr());	//Ψһ��û�����ü��������ܿ���
	unique_ptr<CTestPtr> autop4 = unique_ptr<CTestPtr>(new CTestPtr());
	autop4.get_deleter();
	//�Զ���ɾ��
	unique_ptr<CTestPtr, TestDelete> autop5(new CTestPtr());
	unique_ptr<CTestPtr, TestDelete> autop6(new CTestPtr(), autop5.get_deleter());



	MSharedPtr<CTestPtr2> TestPtr2(new CTestPtr2());
	MSharedPtr<CTestPtr2> TestPtr3(TestPtr2);
	MSharedPtr<CTestPtr2> TestPtr4 = TestPtr2;
	TestPtr4.Release();
	TestPtr3->Init();
	TestPtr3.Release();


	MWeakPtr<CTestPtr2>TestPtr5 = TestPtr2;
	MWeakPtr<CTestPtr2>TestPtr6(TestPtr2);
	TestPtr6.Pin()->Init();
	TestPtr6.Release();




	struct CastTestA :public enable_shared_from_this<CastTestA>
	{
		CastTestA()
			:a(100)
		{}

		//ʹ��dynamic_pointer_cast���뱣֤�����и�һ���麯��
		virtual void Test()
		{}

		int a;
	};
	struct CastTestB :public CastTestA
	{
		CastTestB()
			:b(200)
		{}

		int b;
	};

	shared_ptr<CastTestA> MA(new CastTestB);
	cout << MA->a << endl;
	//MA->b;	//�޷�������Ҫǿת
	shared_ptr<CastTestB>MB = dynamic_pointer_cast<CastTestB>(MA);
	cout << MB->b << endl;


	return 0;
}
