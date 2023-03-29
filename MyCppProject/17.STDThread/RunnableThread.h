/*
*	��ƽ̨
*	�ӿ�
	�����̡߳����𡢻��ѡ��ȴ������߳�
*/

#pragma once

// ue�߳����ȼ�
enum class EThreadPriority
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

class MRunnable
{
public:
	virtual bool Init() { return false; }

	virtual int Run() = 0;

	virtual int Stop() { return 0; }

	virtual int Start() { return 0; }

	virtual bool Exit() { return false; }

	virtual class RunnableThread* GetThread() = 0;
};


class RunnableThread
{
public:
	RunnableThread();
	virtual ~RunnableThread() {}

	virtual bool Create(MRunnable* InRunnable) = 0;

	void SetPriority(EThreadPriority InPriority);
	void SetThreadName(const char* InThreadName);
	void SetThreadID(unsigned int InId);

	const EThreadPriority GetPriority() const;
	const char* GetThreadName() const;
	const unsigned int GetThreadID() const;

	virtual void Suspend() {};
	virtual void Resume() {};

protected:
	EThreadPriority Priority;
	char ThreadName[512];
	unsigned int ThreadID;
};

