/*
*	��ƽ̨
*	�ӿ�
	�����̡߳����𡢻��ѡ��ȴ������߳�
*/

#pragma once
#include "Runnable.h"

// ue�߳����ȼ�
enum EThreadPriority
{
	TPri_Normal,				//����
	TPri_AboveNormal,			//��������
	TPri_BelowNormal,			//��������
	TPri_Highest,				//����
	TPri_Lowest,				//����
	TPri_SlightlyBelowNormal,	//�Ը�������
	TPri_TimeCritical,			//ʱ�򡢴���
	TPri_Num,					//���ȼ�������
};

class RunnableThread
{
public :
	RunnableThread();

	virtual bool Create(MRunnable *InRunnable) = 0;

	void SetPriority(EThreadPriority InPriority);
	void SetThreadName(const char *InThreadName);
	void SetThreadID(unsigned int InId);

	const EThreadPriority GetPriority() const;
	const char *GetThreadName() const;
	const unsigned int GetThreadID() const;

protected:
	EThreadPriority Priority;
	char ThreadName[512];
	unsigned int ThreadID;
};

