#include <iostream>


using namespace std;

int main()
{
	// 裸指针
	int *iPtr = new int;

	// 共享指针	std::shared_ptr
	std::shared_ptr<int>  siPtr1(iPtr);
	std::shared_ptr<int> siPtr2 = std::make_shared<int>(12);	//分配一个空间，并将值设置为12
	std::shared_ptr<int> siPtr3(siPtr1);	//增加引用计数	//敏感检测

	cout << "当前引用计数=" << siPtr1.use_count() << endl;
	siPtr3 = nullptr;	//减少引用计数	不会清除对象 除非计数为0了
	cout << "当前引用计数=" << siPtr1.use_count() << endl;

	std::shared_ptr<int> siPtr4 = siPtr1;



	// 弱指针 std::weak_ptr
	

	return 0;
}