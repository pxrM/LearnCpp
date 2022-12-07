/*
	引用生成的库

	exe：可执行文件	 整合了多个dll
	dll：动态链接库  把代码文件都整合成二进制存在dll文件里，里面存有正真的代码
	lib：静态链接库  #pragma comment(lib, "xxxxxx.lib") 通过头文件和lib文件(也是二进制文件)进行链接
	pdb：调试符号，如果没有就不能调试
	
*/

#include <iostream>
#include "10.library_cpp/Interface.h"
#include "10.library_c/TestC.h"


#pragma comment(lib, "10.library.lib") //静态库 c++
#pragma comment(lib, "10.library_c.lib") //静态库 c

using namespace std;


int main()
{
	IInterface *iif = IInterface::CreateInterface();
	cout << iif->GetName() << endl;
	iif->Init();
	iif->Destroy();



	init_c(1, 66);
	get_c_name(6, 99);

	return 0;
}