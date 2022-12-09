/*
	模板元编程
*/

#pragma once

#include <iostream>

using namespace std;


// 通过模板定义一个值
template<class T, T v>
struct ConstTest
{
	static constexpr T value = v;
};


template<class T>
struct RemoveConst
{
	using Type = T;
};

template<class T>
struct RemoveConst<const T>
{
	using Type = T;
};


template<bool v>
using bool_temp = ConstTest<bool, v>;


template<class, class>
constexpr bool isSame_V = false;

template<class T1>
constexpr bool isSame_V < T1, T1 > = true;

template<class T1, class T2>
struct isSame :bool_temp<isSame_V<T1, T2>> {};