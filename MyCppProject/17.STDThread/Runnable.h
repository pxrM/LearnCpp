/*
	½Ó¿Ú
*/

#pragma once

class MRunnable
{
public:
	virtual bool Init() { return false; }

	virtual int Run() = 0;

	virtual int Stop() { return 0; }

	virtual bool Exit() { return false; }

	virtual RunnableThread *GetThread() = 0;
};

