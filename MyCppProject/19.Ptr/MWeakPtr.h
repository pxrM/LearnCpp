#pragma once

//#include "PtrType.h"


//template<class T>
//class MWeakPtr
//{
//	friend class MSharedPtr<T>;
//
//	MWeakPtr()
//		:Ptr(nullptr)
//		,Count(nullptr)
//	{}
//
//	MWeakPtr(MWeakPtr<T>& InInstance)
//		:Ptr(InInstance.Ptr)
//		,Count(InInstance.Count)
//	{
//		Count->WeakCount++;
//	}
//
//	MWeakPtr<T>& operator=(MWeakPtr<T>& MT)
//	{
//		if (this != MT)
//		{
//			Release();
//
//			Ptr = MT.Ptr;
//			Count = MT.Count;
//
//			Count->WeakCount++;
//		}
//
//		return *this;
//	}
//
//	MWeakPtr<T>& operator=(MSharedPtr<T>& MS)
//	{
//		Release();
//
//		Ptr = MS.Ptr;
//		Count = MS.Count;
//
//		Count->WeakCount++;
//
//		return *this;
//	}
//
//	MSharedPtr<T> Pin()
//	{
//		return MSharedPtr<T>(*this);
//	}
//
//	bool IsValid()
//	{
//		if (Count && Count->WeakCount > 0)
//		{
//			return true;
//		}
//		return false;
//	}
//
//	~MWeakPtr()
//	{
//		Release();
//	}
//
//	void Release()
//	{
//		if (Count)
//		{
//			Count->WeakCount--;
//			if (Count->WeakCount < 1 && Count->SharedCount < 1)
//			{
//				delete Count;
//				Count = nullptr;
//			}
//		}
//	}
//
//private:
//	T* Ptr;
//	MRefCounter* Count;
//};
