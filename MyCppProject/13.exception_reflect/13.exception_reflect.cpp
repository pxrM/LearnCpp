/*
	����ģ��Ͷ�̬
	���쳣����
	����װ���������output
	���Զ��������쳣������

	��std::exception
	��std::bad_alloc��ʹ��newʧ�ܻ�ͨ������׳��쳣��
	��std::bad_cast��dynamic_cast�쳣��
	��std::bad_exception������c++�������޷�Ԥ��Ķ���
	��std::bad_tyoeid��typeid()��
	��std::logic_error���߼�����
	��std::domain_error����Ч��������
	��std::invalid_argument����Ч�Ĳ�����
	��std::length_error��string���ȣ�
	��std::out_of_range��vector����һ����Χ��
	��std::runtime_error����ȡ����ʱ���ֵĴ���
	��std::overflow_error����ѧ�����
	��std::range_error������������Χ��
	��std::underflow_error����ѧ���磩

	��typeid����ȡ���ʽ������Ϣ��
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <atlstr.h>

#include "temptest.h"



// �����debuglog��
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
		out_put_debug_log("��ǰ�������⣺[%s] ", p);
		return p;
	}
};


int main()
{
	TempBB tb;
	TempAA<int> *ta = &tb;
	ta->Init();

	//name ��������
	//raw_name ���ֱ��룬�㷨����
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
	//	throw "b ���� 10";	//�׳��쳣
	//}
	try
	{
		if (b == 10)
		{
			//throw "b ���� 10";	//�׳��쳣
			throw MException();
		}
	}
	catch (const char *Msg)
	{
		cout << Msg << endl;
		out_put_debug_log("��ǰ�������⣺[%s] ", Msg);
		assert(0);
	}
	catch (const MException &Msg)
	{
		cout << Msg.what() << endl;
		assert(0);
	}



	return 0;
}