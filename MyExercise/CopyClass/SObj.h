/*
	 深拷贝会申请一新的内存空间用于存放拷贝过来的内容，即深拷贝拷贝对象的所有成员，
	 包括指针所指向的内存空间也会一起被拷贝，被拷贝过来的指针会指向一个新的内存地址。
*/
#include <iostream>

using namespace std;

//代码1.2
class SObj
{
public:
	SObj(char* tp)
	{
		len = strlen(tp);
		p = (char*)malloc(len + 1);
		strcpy_s(p, len + 1, tp);
	}
	//------------------------------
	/*
		拷贝构造函数--深拷贝
		1.在定义拷贝构造函数时，必须使用引用传递，否则会出现无限拷贝的情况，因为，如果使用值传递的话，
		  在传递对象到拷贝构造函数时，又会调用拷贝构造函数将实参拷贝给形参，而这个过程又会将对象传递给拷贝构造函数，
		  从而在此调用拷贝构造函数将实参拷贝给形参，如此无限循环。
		2.拷贝构造函数只能有一个参数，且必须是自身类的引用
	*/
	SObj(const SObj& obj)
	{
		len = obj.len;
		p = (char*)malloc(len + 1);
		strcpy_s(p, len + 1, obj.p);
	}
	//------------------------------
	~SObj()
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
