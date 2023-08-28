/**
* 
* C++在进行浅拷贝时，只拷贝栈区的内存空间地址，不拷贝堆区的内存空间内容，
* 即浅拷贝只拷贝非指针的成员变量和指针本身，而不拷贝指针所指向的堆区的内容。
* 
*/

#include <iostream>

using namespace std;

//代码1.1
class QObj
{
public:
	QObj(char* tp)
	{
		len = strlen(tp);
		p = (char*)malloc(len + 1); //分配内存空间，大小为 len + 1 字节（包括终止符 \0 的空间），并将分配的内存地址保存到指针变量 p 中。
		strcpy_s(p, len + 1, tp); //将字符串 tp 拷贝到之前分配的内存空间 p 中，确保不会发生内存溢出
	}
	~QObj()
	{
		if (p)
		{
			free(p);
			p = nullptr;
			len = 0;
		}
	}
	void Show()
	{
		cout << *p << *(p + 1) << *(p + 2) << endl;
	}
private:
	char* p;
	int len;
};
