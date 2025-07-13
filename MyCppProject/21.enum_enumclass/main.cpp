#include <iostream> 
#include <vector>

// 枚举值泄露到外层作用域
enum TestA{
	A,
	B,
};
// 编译错误：A重定义
enum TestB
{
	//A,
	C,
};


// 使用enum class可以避免枚举值泄露到外层作用域
enum class CA {
	A,
	B,
};
enum class CB
{
	A,
	C,
};


int main() {

	int a = A;	//直接使用
	CA ca = CA::A; //必须使用作用域限定符
	return 0;
}