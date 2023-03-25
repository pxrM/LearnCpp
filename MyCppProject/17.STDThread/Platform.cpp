/*

*/

#include "Platform.h"
#include <Windows.h>



class FWin32RunnableThread :public RunnableThread
{
public:
	~FWin32RunnableThread()
	{
		if (MH)
		{
			CloseHandle(MH);
		}

	}

	virtual bool Create(MRunnable *InRunnable) override;

	virtual void Suspend() override;
	virtual void Resume() override;

protected:
	HANDLE MH;
};
bool FWin32RunnableThread::Create(MRunnable *InRunnable)
{
	if (InRunnable)
	{
		auto RunThread = [](LPVOID lpPram)->DWORD
		{
			MRunnable *mRunnable = (MRunnable *)lpPram;
			RunnableThread *MyThread = mRunnable->GetThread();
			MyThread->SetThreadID(GetCurrentThreadId());
#ifdef _WIN32
			struct FTagThreadNameInfo
			{
				DWORD dwType; //0x1000 4096
				LPCSTR szName;
				DWORD dwThreadID; //�����̵߳�id
				DWORD dwFlags;	//��־λ
			};
			FTagThreadNameInfo Info;
			Info.dwType = 0x1000;
			Info.szName = MyThread->GetThreadName();
			Info.dwThreadID= MyThread->GetThreadID();
			Info.dwFlags = 0;
			// 0x406D1388�̶������׳��쳣�Ĵ���
			// 0Ϊ�ɳ����쳣
			// sizeof(Info)/sizeof(DWORD)��ȡ��������
			RaiseException(0x406D1388, 0, sizeof(Info) / sizeof(DWORD), (ULONG_PTR*)(&Info));
#elif __linux

#endif // _WIN32
			DWORD returnVal = mRunnable->Run();
			mRunnable->Exit();

			return returnVal;
		};
		MH = CreateThread(nullptr, 0, RunThread, InRunnable, 0, nullptr);
		return true;
	}
	return false;
}

void FWin32RunnableThread::Suspend()
{
	SuspendThread(MH);
}

void FWin32RunnableThread::Resume()
{
	ResumeThread(MH);
}



class FLinuxRunnableThread :public RunnableThread
{
public:
	virtual bool Create(MRunnable *InRunnable) override;
};
bool FLinuxRunnableThread::Create(MRunnable *InRunnable)
{
	if (InRunnable)
	{
		return true;
	}
	return false;
}


RunnableThread *Platform::Create(
	MRunnable *InRunnable,
	const char *InThreadName,
	const EThreadPriority InPriority,
	unsigned int InStack
)
{
	RunnableThread *rnThread = nullptr;

#ifdef _WIN32
	if (InRunnable->Init())
	{
		rnThread = new FWin32RunnableThread();
		//��ʼ��
		rnThread->SetPriority(InPriority);
		rnThread->SetThreadName(InThreadName);
		//ִ��
		rnThread->Create(InRunnable);
	}

#elif __linux
	if (InRunnable->Init())
	{
		rnThread = new FLinuxRunnableThread();
	}
	
#endif // _WIN32


	return rnThread;
}

