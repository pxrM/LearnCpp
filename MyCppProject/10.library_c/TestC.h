/*
*	封装c库
*
*		动态链接库：运行时把代码链接到目标
*		静态链接库：编译时把代码链接到目标
*/

#ifndef TESTC_H
#define TESTC_H

// 定义导出宏，方便在Windows下导出符号
#define LIBRARY_C_API __declspec(dllexport)


/*
	#ifdef __cplusplus

	如果当前头文件是给C++使用的话，__cplusplus值就为1，这样好处是c++在调用的时候就会告诉编译器这个代码是c语言写的
		此时宏展开为：
			extern "C"	//告诉编译器这里面的是c语言代码
			{
				LIBRARY_C_API int __stdcall init_c(int a, int b);
				LIBRARY_C_API int __stdcall get_c_name(int a, int b);
				int get_c_private(int a, int b);
			}

	如果是C语言的话，值就为0，
		此时宏展开为：
			LIBRARY_C_API int __stdcall init_c(int a, int b);
			LIBRARY_C_API int __stdcall get_c_name(int a, int b);
			int get_c_private(int a, int b);
*/


#ifdef __cplusplus
extern "C"	//告诉编译器这里面的是c语言代码
{
#endif 
	// __stdcall：指定函数调用约定，参数从左到右通过堆栈传递，常用于Windows API

	// 初始化函数，导出给外部使用
	LIBRARY_C_API int __stdcall init_c(int a, int b);
	// 获取名称函数，导出给外部使用
	LIBRARY_C_API int __stdcall get_c_name(int a, int b);
	// 私有函数，仅供内部使用，不导出
	int get_c_private(int a, int b);

#ifdef __cplusplus
}
#endif



#endif // !TESTC_H
