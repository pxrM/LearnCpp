#pragma once

#include "PtrType.h"

/// <summary>
/// ÷«ƒ‹÷∏’Î¿‡
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class MSharedPtr
{
public:
	//MSharedPtr<Test> Instance(new Test)
	MSharedPtr(T *InInstance = nullptr)
		:Ptr(InInstance)
	{
		Count = new MRefCounter();
		if (InInstance)
		{
			Count->SharedCount = 1;
		}
	}

	//MSharedPtr<Test> Instance(new Test)
	//MSharedPtr<Test> Instance(InInstance)
	MSharedPtr(MSharedPtr<T> &InInstance)
	{
		Ptr = InInstance.Ptr;
		InInstance.Count->SharedCount++;
		Count = InInstance.Count;
	}

	//MSharedPtr<Test> Instance(new Test)
	//MSharedPtr<Test> Instance(InInstance)
	//MSharedPtr<Test> Instance = InInstance
	MSharedPtr<T> &operator=(MSharedPtr<T> &InInstance)
	{
		if (this != &InInstance)
		{
			Release();
			InInstance.Count.SharedCount++;
			this->Count = InInstance.Count;
			this->Ptr = InInstance.Ptr;
		}

		return *this;
	}

	T *operator*()
	{
		return *Ptr;
	}

	T *operator->()
	{
		return Ptr;
	}

	void Release()
	{
		Count->SharedCount--;
		if (Count->SharedCount <= 0)
		{
			return;
		}
		if (Count->SharedCount < 1)
		{
			if (Count->WeakCount < 1)
			{
				delete Count;
				Count = nullptr;
			}

			delete Ptr;
			Ptr = nullptr;
		}
	}

	~MSharedPtr()
	{
		Release();
	}

private:
	T *Ptr;
	MRefCounter *Count;

};

