/*
	引用生成的库
	
*/

#include <iostream>
#include "10.library_cpp/Interface.h"

#pragma comment(lib, "10.library.lib") //静态库

using namespace std;


int main()
{
	IInterface *iif = IInterface::CreateInterface();

	cout << iif->GetName() << endl;
	iif->Init();
	iif->Destroy();

	return 0;
}