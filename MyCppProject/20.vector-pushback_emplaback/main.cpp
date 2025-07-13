#include <iostream> 
#include <vector>


class A
{
public:
	A(int v) : a(v) {
		std::cout << "A(int v) 构造函数被调用，a = " << a << std::endl;
	}

	A(const A& other) : a(other.a) {
		std::cout << "A(const A& other) 拷贝构造函数被调用，a = " << a << std::endl;
	}

	A(A&& other) noexcept : a(other.a) {
		std::cout << "A(A&& other) 移动构造函数被调用，a = " << a << std::endl;
	}

	~A() {
		std::cout << "A 析构函数被调用，a = " << a << std::endl;
	}

public:
	int a;
};



int main()
{
	/*
	* 
	* vector的扩容机制：
	*	std::vector 采用 指数增长策略，即每次扩容时 容量（capacity）约为当前的 1.5 - 2 倍。
	*	扩容步骤：
	*		申请更大内存（通常是当前 capacity 的 1.5 - 2 倍）。
	*		拷贝或移动旧数据 到新内存。
	*		释放旧内存。
	*	优化：如果已知需要存储大量数据，可使用reserve(n)预分配空间，避免多次扩容。
	*		vec.reserve(1000);  // 直接预分配 1000 个元素的空间
	* 
	* 两者都是vector的成员函数，用于向vector中末尾添加元素。
	*	主要区别在于添加元素的方式：
	*	push_back：接受一个已存在的对象作为参数，进行拷贝或移动操作，将其添加到vector的末尾。
	*			这会触发一次拷贝或移动构造函数。具体取决于传递的对象是否可以移动。（如果有移动构造会优先调用移动构造）
	*	emplace_back：接受对象构造函数的参数，直接在vector的内存空间中调用该对象的构造函数，避免额外的拷贝或移动操作。
	*				避免了不必要的对象构造和析构及拷贝或移动。可以提高性能，尤其是当对象较大或复杂时。
	* 
	*/
	std::cout << "1.vector的扩容机制" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::vector<int> vecK;
	for (int i = 1; i <= 10; ++i) {
		vecK.push_back(i);
		std::cout << "Size: " << vecK.size() << ", Capacity: " << vecK.capacity() << std::endl;
	}
	std::cout << "" << std::endl;

	std::cout << "2.std::vector 的 push_back 和 emplace_back 的区别" << std::endl;
	std::vector<std::string> vecStr;
	vecStr.push_back("Hello");		// 先创建string对象，然后将其拷贝到vector中。（先构造再拷贝）
	vecStr.emplace_back("World");	// 直接在vector的内存空间中构造string对象。（避免了拷贝构造）

	std::vector<A> vecA;
	vecA.push_back(A(1));		// 先创建A对象，然后将其拷贝到vector中。（先构造再拷贝）
	std::cout << "----------------------------------------" << std::endl;
	vecA.emplace_back(2);		// 直接在vector的内存空间中构造A对象。（避免了拷贝构造）


	std::cout << "----------------------------------------" << std::endl;

	return 0;
}