/*
	�������ɵĿ�

	exe����ִ���ļ�	 �����˶��dll
	dll����̬���ӿ�  �Ѵ����ļ������ϳɶ����ƴ���dll�ļ�������������Ĵ���
	lib����̬���ӿ�  #pragma comment(lib, "xxxxxx.lib") ͨ��ͷ�ļ���lib�ļ�(Ҳ�Ƕ������ļ�)��������
	pdb�����Է��ţ����û�оͲ��ܵ���
	
*/

#include <iostream>
#include "10.library_cpp/Interface.h"
#include "10.library_c/TestC.h"


#pragma comment(lib, "10.library.lib") //��̬�� c++
#pragma comment(lib, "10.library_c.lib") //��̬�� c

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