/*
	·类模板和多态
	·异常处理
	·封装任意参数到output
	·自定义任意异常处理类
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <atlstr.h>

#include "temptest.h"



// 输出到debuglog里
void out_put_debug_log(const char *in_format, ...)
{
	char buffer[8196] = { 0 };
	va_list in_args;
	va_start(in_args, in_format);
	_vsnprintf(buffer, sizeof(buffer) - 1, in_format, in_args);
	va_end(in_args);

	OutputDebugString(CA2W(buffer));
}

char p[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
struct MException :public exception {
	const char *what() const throw() {
		out_put_debug_log("当前出现问题：[%s] ", p);
		return p;
	}
};


int main()
{
	TempBB tb;
	TempAA<int> *ta = &tb;
	ta->Init();


	int b = 10;
	//if (b == 10)
	//{
	//	throw "b 等于 10";	//抛出异常
	//}
	try
	{
		if (b == 10)
		{
			//throw "b 等于 10";	//抛出异常
			throw MException();
		}
	}
	catch (const char *Msg)
	{
		cout << Msg << endl;
		out_put_debug_log("当前出现问题：[%s] ", Msg);
		assert(0);
	}
	catch (const MException &Msg)
	{
		cout << Msg.what() << endl;
		assert(0);
	}



	return 0;
}