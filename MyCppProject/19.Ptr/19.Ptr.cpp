#include <iostream>


using namespace std;


//enable_shared_from_this  会在内部保存一个弱指针
class CTestPtr :public enable_shared_from_this<CTestPtr>
{
public:
	void Init()
	{

	}
};


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

	// 弱指针 std::weak_ptr
	

	return 0;
}