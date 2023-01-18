/*
	����ƽ̨������ͬ�߳�
*/

#pragma once
#include "RunnableThread.h"


class Platform
{
public:
	static RunnableThread *Create(
		MRunnable *InRunnable,
		const char *InThreadName,
		const EThreadPriority InPriority = EThreadPriority::TPri_Normal, 
		unsigned int InStack = 0
	);
};

