/*
*	��װc��
*
*		��̬���ӿ⣺����ʱ�Ѵ������ӵ�Ŀ��
*		��̬���ӿ⣺����ʱ�Ѵ������ӵ�Ŀ��
*/

#ifndef TESTC_H
#define TESTC_H

// ���嵼���꣬������Windows�µ�������
#define LIBRARY_C_API __declspec(dllexport)


/*
	#ifdef __cplusplus

	�����ǰͷ�ļ��Ǹ�C++ʹ�õĻ���__cplusplusֵ��Ϊ1�������ô���c++�ڵ��õ�ʱ��ͻ���߱��������������c����д��
		��ʱ��չ��Ϊ��
			extern "C"	//���߱��������������c���Դ���
			{
				LIBRARY_C_API int __stdcall init_c(int a, int b);
				LIBRARY_C_API int __stdcall get_c_name(int a, int b);
				int get_c_private(int a, int b);
			}

	�����C���ԵĻ���ֵ��Ϊ0��
		��ʱ��չ��Ϊ��
			LIBRARY_C_API int __stdcall init_c(int a, int b);
			LIBRARY_C_API int __stdcall get_c_name(int a, int b);
			int get_c_private(int a, int b);
*/


#ifdef __cplusplus
extern "C"	//���߱��������������c���Դ���
{
#endif 
	// __stdcall��ָ����������Լ��������������ͨ����ջ���ݣ�������Windows API

	// ��ʼ���������������ⲿʹ��
	LIBRARY_C_API int __stdcall init_c(int a, int b);
	// ��ȡ���ƺ������������ⲿʹ��
	LIBRARY_C_API int __stdcall get_c_name(int a, int b);
	// ˽�к����������ڲ�ʹ�ã�������
	int get_c_private(int a, int b);

#ifdef __cplusplus
}
#endif



#endif // !TESTC_H
