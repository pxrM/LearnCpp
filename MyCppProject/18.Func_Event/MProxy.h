#pragma once

#include <iostream>
#include <vector>


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

/// <summary>
/// 工厂
/// </summary>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
template<class TReturn, typename ...ParamTypes>
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

	virtual TReturn Execute(ParamTypes &&...Params)
	{
		return CurrentDelegatePtr->Execute(std::forward<ParamTypes>(Params)...);
	}

private:
	DelegateBase<TReturn, ParamTypes...> *CurrentDelegatePtr;
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

/// <summary>
/// 单播代理
/// </summary>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
template<class TReturn, typename ...ParamTypes>
class SingleDelegate :public FactoryDelegate<TReturn, ParamTypes...>
{
public:
	SingleDelegate() :FactoryDelegate<TReturn, ParamTypes...>()
	{
	}

};


#define SIMPLE_SINGLE_DELEGATE(Name, Return, ...) SingleDelegate<Return, __VA_ARGS__> Name;

#define DEFINITION_SIMPLE_SINGLE_DELEGATE(DefinitionName, Return, ...)\
class DefinitionName : public SingleDelegate<Return, __VA_ARGS__>\
{};\

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

/// <summary>
/// 多播代理
/// </summary>
/// <typeparam name="TReturn"></typeparam>
/// <typeparam name="...ParamTypes"></typeparam>
template<class TReturn, typename ...ParamTypes>
class MulticastDelegate :public std::vector<FactoryDelegate<TReturn, ParamTypes...>>
{
	typedef FactoryDelegate<TReturn, ParamTypes...> TDelegate;

public:
	MulticastDelegate()
	{
	}

	template<class TObjectType>
	void AddFunction(TObjectType *InObject, TReturn(TObjectType:: *InObjFunction)(ParamTypes...))
	{
		this->emplace_back(TDelegate());
		TDelegate &InDelegate = this->back();
		InDelegate.Bind(InObject, InObjFunction);
	}

	void AddFunction(TReturn(InFunction)(ParamTypes...))
	{
		this->emplace_back(TDelegate());
		TDelegate &InDelegate = this->back();
		InDelegate.Bind(InFunction);
	}

	void Broadcast(ParamTypes &&...Params)
	{
		for (auto &Temp : *this)
		{
			Temp.Execute(std::forward<ParamTypes>(Params)...);
		}
	}

	void ReleaseDelegates()
	{
		for (auto &Temp : *this)
		{
			Temp.ReleaseDelegate();
		}
	}
};

#define SIMPLE_MULTICAST_DELEGATE(Name, Return, ...) MulticastDelegate<Return, __VA_ARGS__> Name;
#define DEFINITION_MULTICAST_SINGLE_DELEGATE(DefinitionName, Return, ...) class DefinitionName : public MulticastDelegate<Return, __VA_ARGS__>{};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class TObjectType, class TReturn, typename ...ParamTypes>
MObjectDelegate<TObjectType, TReturn, ParamTypes...>CreateMObjectDelegate(TObjectType *InObj, TReturn(TObjectType:: *InFunc)(ParamTypes...))
{
	return MObjectDelegate<TObjectType, TReturn, ParamTypes...>(InObj, InFunc);
}