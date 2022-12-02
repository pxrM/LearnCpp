#include <iostream>

class Monster
{
public:
	Monster();
	~Monster();

	int a;
	int b;

	/* 
	编译器会在编译阶段，会把该函数的代码复制到调用该函数的地方。
	内联可以使用在内成员和结构体以及全局函数中
	需要注意的地方：
		1.内联函数最好放在.h文件中，声明和定义不会分开
		2.内联函数一般需要简短的代码，最好不要出现循环、递归、Switch以及一些复杂的运算，否则会影响效率
	*/
	inline int GetP()const {
		return b;
	}

private:

};

Monster::Monster()
{

}

Monster::~Monster()
{
}

void main()
{
}