#include <iostream>


using namespace std;


//enable_shared_from_this  会在内部保存一个弱指针	UE：TSharedFromThis
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

	IInterface *CreateInterface()
	{
		IInterface *face = new B();
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



int main()
{
	// 裸指针
	int *iPtr = new int;

	// 共享指针	std::shared_ptr
	std::shared_ptr<int>  siPtr1(iPtr);
	std::shared_ptr<int> siPtr2 = std::make_shared<int>(12);	//分配一个空间，并将值设置为12
	std::shared_ptr<int> siPtr3(siPtr1);	//增加引用计数	//敏感检测
	std::shared_ptr<int> siPtr4 = siPtr1;
	cout << "当前引用计数=" << siPtr1.use_count() << endl;
	siPtr4 = nullptr;	//减少引用计数	不会清除对象 除非计数为0了
	cout << "当前引用计数=" << siPtr1.use_count() << endl;
	int *iPtr2 = siPtr1.get();	//转为原始指针（裸指针）
	int ivalue = *siPtr1;	//获取值
	bool bSingle = siPtr1.unique(); //是不是唯一的
	//siPtr1.swap(siPtr2);	//交换
	siPtr1.reset();	//reset = (siPtr1 = nullptr)

	shared_ptr<CTestPtr> ctsptr1(new CTestPtr);
	CTestPtr *ctptr = ctsptr1.get();	//转裸指针
	shared_ptr<CTestPtr> ctsptr2 = ctptr->shared_from_this();	//转共享指针

	// 弱指针 std::weak_ptr		UE4：TWeakPtr
	std::weak_ptr<CTestPtr> swp1 = ctsptr2;
	swp1.lock()->Init();	//lock()转化为共享指针并增加引用计数
	if (swp1.use_count() == 0 || swp1.expired())
	{
		cout << "失效了" << endl;
	}



	ATest ATest1;
	IInterface *ii = ATest1.CreateInterface();
	ii->DoWork();


	return 0;
}
