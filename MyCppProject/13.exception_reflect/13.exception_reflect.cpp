/*
	·类模板和多态
	·异常处理
*/

#include <iostream>
#include <cassert>

#include "temptest.h"


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
			throw "b 等于 10";	//抛出异常
		}
	}
	catch (const char *Msg)
	{
		cout << Msg << endl;
		assert(0);
	}



	return 0;
}