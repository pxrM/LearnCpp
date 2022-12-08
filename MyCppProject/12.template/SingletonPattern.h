/*
	·单例
*/

#pragma once

#include <iostream>

using namespace std;

template<class T>
class MThread
{
public:
	static T *Get()
	{
		if (!Instance)
		{
			Instance = new T();
		}
		return Instance;
	}
	static void Destroy()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

private:
	static T *Instance;
};

//因为是静态的所以要声明
template<class T>
T *MThread<T>::Instance = nullptr;



class MThreadTest
{
public:
	void Func()
	{
		cout << "MThreadTest Func" << endl;
	}
};


typedef MThread<MThreadTest> TTTest;



#define D_THREAD(TName, TInstance) \
template<class T> \
class MThread_##TName \
{ \
public: \
	static T *Get() \
	{ \
		if (!Instance) \
		{ \
			Instance = new T(); \
		} \
		return Instance; \
	} \
	static void Destroy() \
	{ \
		if (Instance) \
		{ \
			delete Instance; \
			Instance = nullptr; \
		} \
	} \
private: \
	static T *Instance; \
}; \
template<class T>  \
T *MThread_##TName<T>::Instance = nullptr; \
typedef MThread_##TName<TInstance> TName; //typedef MThread<MThreadTest> TTTest;


class MThreadTest_Two
{
public:
	void Func()
	{
		cout << "MThreadTest_Two Func" << endl;
	}
};

class MThreadTest_Three
{
public:
	void Func()
	{
		cout << "MThreadTest_Three Func" << endl;
	}
};

D_THREAD(Two, MThreadTest_Two)
D_THREAD(Three, MThreadTest_Three)
