/*
*	��װcƨƨ��
* 
*		��̬���ӿ⣺����ʱ�Ѵ������ӵ�Ŀ��
*		��̬���ӿ⣺����ʱ�Ѵ������ӵ�Ŀ��
*/


//#pragma once	//��ֹ�����ļ��ڰ������ļ�ʱ�ظ����������Ƿ�ʽһ
// 

#ifndef INTERFACE_H	//��ʽ����ʹ�ú�ķ�ʽ���жϵ�ǰ��û�ж�������ļ�
#define INTERFACE_H //���û�ж�������ж���
#define _CRT_SECURE_NO_WARNINGS

#define LIBRARY_CPP_API __declspec(dllexport)  //ר���������Ĺؼ���


//���϶���� LIBRARY_CPP_API ������ӿھͿ��Ե�������������ʹ����
class LIBRARY_CPP_API IInterface
{
public:
	static IInterface *CreateInterface();

	//static LIBRARY_CPP_API IInterface *CreateInterface(); ֻ���Ⱪ¶����ӿ�

	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual char *GetName() = 0;

};



#endif // INTERFACE_H
