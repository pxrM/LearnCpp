/*
	����ģ��Ͷ�̬
	���쳣����
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
	//	throw "b ���� 10";	//�׳��쳣
	//}
	try
	{
		if (b == 10)
		{
			throw "b ���� 10";	//�׳��쳣
		}
	}
	catch (const char *Msg)
	{
		cout << Msg << endl;
		assert(0);
	}



	return 0;
}