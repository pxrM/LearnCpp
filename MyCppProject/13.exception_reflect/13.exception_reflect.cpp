/*
	·类模板和多态
	·异常处理
	·封装任意参数到output
	·自定义任意异常处理类

	·std::exception
	·std::bad_alloc（使用new失败会通过这个抛出异常）
	·std::bad_cast（dynamic_cast异常）
	·std::bad_exception（处理c++程序中无法预测的对象）
	·std::bad_tyoeid（typeid()）
	·std::logic_error（逻辑出错）
	·std::domain_error（无效的数据域）
	·std::invalid_argument（无效的参数）
	·std::length_error（string长度）
	·std::out_of_range（vector超出一定范围）
	·std::runtime_error（读取代码时出现的错误）
	·std::overflow_error（数学溢出）
	·std::range_error（容器超出范围）
	·std::underflow_error（数学下溢）

	·typeid（获取表达式类型信息）
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

	//name 类型名字
	//raw_name 名字编码，算法产出
	//hash_code	id
	int aaaa = 10;
	const type_info &info = typeid(aaaa);
	cout << "name = " << info.name() << "   raw_name = " << info.raw_name() << "   hash_code = " << info.hash_code() << endl;
	const type_info &info2 = typeid(tb);
	cout << "name = " << info2.name() << "   raw_name = " << info2.raw_name() << "   hash_code = " << info2.hash_code() << endl;
	const type_info &info3 = typeid(10 * 20 / 100);
	cout << "name = " << info3.name() << "   raw_name = " << info3.raw_name() << "   hash_code = " << info3.hash_code() << endl;


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