/*
*	封装c库
*
*		动态链接库：运行时把代码链接到目标
*		静态链接库：编译时把代码链接到目标
*/

#ifndef TESTC_H
#define TESTC_H

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
	// __stdcall 它修饰的函数参数都是从左到右通过堆栈进行专递

	LIBRARY_C_API int __stdcall init_c(int a, int b);

	LIBRARY_C_API int __stdcall get_c_name(int a, int b);

	int get_c_private(int a, int b);

#ifdef __cplusplus
}
#endif



#endif // !TESTC_H
