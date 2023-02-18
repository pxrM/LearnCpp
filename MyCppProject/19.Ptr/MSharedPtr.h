#pragma once

#include "PtrType.h"
#include "MWeakPtr.h"


template<class T>
class MWeakPtr;

/// <summary>
/// ÷«ƒ‹÷∏’Î¿‡
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class MSharedPtr
{
	friend class MWeakPtr<T>;

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

	MSharedPtr(MWeakPtr<T>& InInstance)
	{
		this->Count = InInstance.Count;
		this->Ptr = InInstance.Ptr;

		this->Count->SharedCount++;
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

	MSharedPtr<T>& operator=(MWeakPtr<T>& InInstance)
	{
		if (this->Ptr != InInstance.Ptr)
		{
			Release();

			this->Count = InInstance.Count;
			this->Ptr = InInstance.Ptr;

			this->Count->SharedCount++;
		}
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



template<class T>
class MWeakPtr
{
	friend class MSharedPtr<T>;

public:
	MWeakPtr()
		:Ptr(nullptr)
		, Count(nullptr)
	{}

	MWeakPtr(MWeakPtr<T>& InInstance)
		:Ptr(InInstance.Ptr)
		, Count(InInstance.Count)
	{
		Count->WeakCount++;
	}

	MWeakPtr(MSharedPtr<T>& InInstance)
		:Ptr(InInstance.Ptr)
		, Count(InInstance.Count)
	{
		Count->WeakCount++;
	}

	MWeakPtr<T>& operator = (MWeakPtr<T>& MT)
	{
		if (this != MT)
		{
			Release();

			Ptr = MT.Ptr;
			Count = MT.Count;

			Count->WeakCount++;
		}

		return *this;
	}

	MWeakPtr<T>& operator = (MSharedPtr<T>& MS)
	{
		Release();

		Ptr = MS.Ptr;
		Count = MS.Count;

		Count->WeakCount++;

		return *this;
	}

	MSharedPtr<T> Pin()
	{
		 MSharedPtr<T> SP(*this);
		 return SP;
	}

	bool IsValid()
	{
		if (Count && Count->WeakCount > 0)
		{
			return true;
		}
		return false;
	}

	~MWeakPtr()
	{
		Release();
	}

	void Release()
	{
		if (Count)
		{
			Count->WeakCount--;
			if (Count->WeakCount < 1 && Count->SharedCount < 1)
			{
				delete Count;
				Count = nullptr;
			}
		}
	}

private:
	T* Ptr;
	MRefCounter* Count;
};


