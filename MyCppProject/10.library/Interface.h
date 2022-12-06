/*
*	封装c屁屁库
* 
*		动态链接库
*		静态链接库
*/


//#pragma once	//防止其它文件在包含该文件时重复包含，这是方式一
// 

#ifndef INTERFACE_H	//方式二：使用宏的方式，判断当前有没有定义这个文件
#define INTERFACE_H //如果没有定义则进行定义
#define _CRT_SECURE_NO_WARNINGS

#define LIBRARY_CPP_API __declspec(dllexport)  //专门做导出的关键字


//加上定义的 LIBRARY_CPP_API 宏这个接口就可以导出给其它工程使用了
class LIBRARY_CPP_API IInterface
{
public:
	static IInterface *CreateInterface();

	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual char *GetName() = 0;

};



#endif // INTERFACE_H
