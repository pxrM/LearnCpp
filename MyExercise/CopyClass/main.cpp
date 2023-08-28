#include "QObj.h"
#include "SObj.h"

/// <summary>
/// 浅拷贝测试
/// </summary>
/// <param name="obj"></param>
void ShallowCopy(QObj& obj)
{
	// 编译器将调用默认的拷贝构造函数，编译器默认的拷贝构造函数是一个浅拷贝，
	// 所以新创建的对象obj2没有自己的堆区空间，obj2.p指向的是obj1.p所指向的内存地址。
	QObj obj2 = obj;
	obj2.Show();
}

int main()
{
	/*
	* 下面的代码编译是通不过的， 原因在于，对象析构时，同一个内存地址0x0001被对象obj1和obj2一起析构了两次。
	* 当代码执行完test(obj1)时，对象obj2被析构，指针obj2.p所指向的内存地址0x0001被释放，
	* 所以当代码执行到obj1.Show()时，使用了已经被释放掉的内存0x0001地址，从而导致运行错误。
	*/
	//QObj obj1(const_cast<char*>("123"));
	//ShallowCopy(obj1);
	//obj1.Show();

	SObj obj3((char*)"asd");
	SObj obj4((char*)"fgh");
	// ERR  此时，在obj3=obj1;处依旧调用默认的拷贝构造函数。因为左操作数已经是一个已经定义的变量，所以并不会调用拷贝构造函数。
	//obj4 = obj3; 
	/*
		这里我们要弄清楚obj3=obj1和Obj obj3 = obj1之间的区别:
			obj4 = obj3; 是将obj3赋值给obj4，=赋值与拷贝构造没有什么关联，
					=在赋值时是c++编译器自己调用默认的拷贝构造（浅拷贝），和类中有无定义深拷贝无关；
			SObj obj5 = obj4; 这里是使用obj4来构造obj5，此时如果类中定义了深拷贝构造函数，就会使用深拷贝。
		要解决这个问题，需要显示重载=运算符了。
	*/
	SObj obj5 = obj4;

	system("pause");

	return 0;
}
