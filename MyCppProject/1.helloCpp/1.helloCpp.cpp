// holleCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 
// c和c++的一些基本区别
//

#include <iostream> // <xxx>表示引用系统文件


/////////////// 形参引用不同 ///////////////
struct FHello
{
	int a;
	int b;
	long int c;
};
void Fun_Cpp(int& cpp, FHello& fh) // cpp支持传引用，c语言不支持
{
	fh.a = 0;
}

void Fun_Ptr(FHello* fhPtr) //指针本身就是个对象，会占四个字节，使用指针传递参数会拷贝指针
{
	fhPtr->a = 0;
}
/////////////////////////////////////////////
// 
/////////////// 结构体不同 ///////////////
struct FStruct
{
	int a;
	int b;
	long int c;

	//cpp的结构体可以直接实现函数，c语言的结构体中只能放入函数指针
	void Func() {}
};
/////////////////////////////////////////////

/////////////// cpp有继承 c语言没有 ///////////////
struct Super
{
	int a;
	int b;
};

struct Child :public Super
{
	void Hello(int x, int y) {}
};

int main()
{
	/////////////// 打印不同 ///////////////
	printf("Hello World! C \n");
	std::cout << "Hello World! Cpp \n";

	/////////////// 变量不同 ///////////////
	bool bOk = false;
	// #include "stdbool.h" //c语言需要包含bool的头文件

	/////////////// 形参引用不同 ///////////////
	FHello fh;
	int testIdx = 0;
	Fun_Cpp(testIdx, fh);
	Fun_Ptr(&fh);

	/////////////// cpp有继承 c语言没有 ///////////////
	Child child;
	child.a = 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
