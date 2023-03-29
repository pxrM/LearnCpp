/*
*	跨平台
*	接口
	创建线程、挂起、唤醒、等待其它线程
*/

#pragma once

// ue线程优先级
enum class EThreadPriority
{
	TPri_Normal,				//正常
	TPri_AboveNormal,			//高于正常
	TPri_BelowNormal,			//低于正常
	TPri_Highest,				//极高
	TPri_Lowest,				//极低
	TPri_SlightlyBelowNormal,	//略高于正常
	TPri_TimeCritical,			//时序、次序
	TPri_Num,					//优先级的数量
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

