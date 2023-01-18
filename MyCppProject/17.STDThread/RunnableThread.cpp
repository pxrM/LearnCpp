#include "RunnableThread.h"
#include <corecrt_memory.h>

RunnableThread::RunnableThread()
	:Priority(EThreadPriority::TPri_Normal)
	,ThreadID(0u)
{
	memset(ThreadName, 0, 512);	//清理下内存
}

void RunnableThread::SetPriority(EThreadPriority InPriority)
{
	Priority = InPriority;
}

void RunnableThread::SetThreadName(const char *InThreadName)
{
	memcpy(ThreadName, InThreadName, 512);
}

void RunnableThread::SetThreadID(unsigned int InId)
{
	ThreadID = InId;
}

const EThreadPriority RunnableThread::GetPriority() const
{
	return Priority;
}

const char *RunnableThread::GetThreadName() const
{
	return ThreadName;
}

const unsigned int RunnableThread::GetThreadID() const
{
	return ThreadID;
}
