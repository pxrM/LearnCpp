#pragma once

#include <iostream>


template<class TReturn, typename ...ParamTypes>
/// <summary>
/// 接口
/// </summary>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
class DelegateBase
{
public:
	virtual TReturn Execute(ParamTypes &&...Params)
	{
		return TReturn();
	}
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class TObjectType, class TReturn, typename ...ParamTypes>
/// <summary>
/// 对象函数代理
/// </summary>
/// <typeparam name="TObjectType"></typeparam>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
class MObjectDelegate :public DelegateBase<TReturn, ParamTypes...>
{
public:
	MObjectDelegate(TObjectType *InObj, TReturn(TObjectType:: *InFunc)(ParamTypes...))
		:Object(InObj)
		, Funcation(InFunc)
	{
	}

	//重载()操作符
	virtual TReturn Execute(ParamTypes &&...Params) override
	{
		return (Object->*Funcation)(std::forward<ParamTypes>(Params)...);
	}

private:
	TObjectType *Object;
	TReturn(TObjectType:: *Funcation)(ParamTypes...);
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class TReturn, typename ...ParamTypes>
/// <summary>
/// 函数代理
/// </summary>
class MFuncDelegate :public DelegateBase<TReturn, ParamTypes...>
{
public:
	MFuncDelegate(TReturn(*InFunc)(ParamTypes...))
		:Funcation(InFunc)
	{
	}

	//重载()操作符
	virtual TReturn Execute(ParamTypes &&...Params) override
	{
		return (*Funcation)(std::forward<ParamTypes>(Params)...);
	}

private:
	TReturn(*Funcation)(ParamTypes...);
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class TReturn, typename ...ParamTypes>
/// <summary>
/// 工厂
/// </summary>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
class FactoryDelegate
{
public:
	FactoryDelegate()
		:CurrentDelegatePtr(nullptr)
	{
	}

	~FactoryDelegate()
	{
		//ReleaseDelegate();
	}

	void ReleaseDelegate()
	{
		if (CurrentDelegatePtr)
		{
			delete CurrentDelegatePtr;
			CurrentDelegatePtr = nullptr;
		}
	}

	FactoryDelegate<TReturn, ParamTypes...> &operator = (const FactoryDelegate<TReturn, ParamTypes...> &InDelegate)
	{
		CurrentDelegatePtr = InDelegate.CurrentDelegatePtr;
		return *this;
	}

public:
	template<class TObjectType>
	static FactoryDelegate<TReturn, ParamTypes...> Create(TObjectType *InObject, TReturn(TObjectType:: *InObjFunction)(ParamTypes...))
	{
		FactoryDelegate<TReturn, ParamTypes...> DelegateInstance;
		DelegateInstance.Bind(InObject, InObjFunction);
		return DelegateInstance;
	}

	static FactoryDelegate<TReturn, ParamTypes...> Create(TReturn(InFunction)(ParamTypes...))
	{
		FactoryDelegate<TReturn, ParamTypes...> DelegateInstance;
		DelegateInstance.Bind(InFunction);
		return DelegateInstance;
	}

public:
	bool IsBound()
	{
		return CurrentDelegatePtr != nullptr;
	}

	template<class TObjectType>
	void Bind(TObjectType *InObject, TReturn(TObjectType:: *InObjFunction)(ParamTypes...))
	{
		ReleaseDelegate();
		CurrentDelegatePtr = new MObjectDelegate<TObjectType, TReturn, ParamTypes...>(InObject, InObjFunction);
	}

	void Bind(TReturn(InFunction)(ParamTypes...))
	{
		ReleaseDelegate();
		CurrentDelegatePtr = new MFuncDelegate<TReturn, ParamTypes...>(InFunction);
	}

	TReturn Execute(ParamTypes &&...Params)
	{
		return CurrentDelegatePtr->Execute(std::forward<ParamTypes>(Params)...);
	}

private:
	DelegateBase<TReturn, ParamTypes...> *CurrentDelegatePtr;
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class TObjectType, class TReturn, typename ...ParamTypes>
MObjectDelegate<TObjectType, TReturn, ParamTypes...>CreateMObjectDelegate(TObjectType *InObj, TReturn(TObjectType:: *InFunc)(ParamTypes...))
{
	return MObjectDelegate<TObjectType, TReturn, ParamTypes...>(InObj, InFunc);
}