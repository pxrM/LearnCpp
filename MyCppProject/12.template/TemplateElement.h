/*
	简单的模板元编程例子
*/

#pragma once

#include <iostream>

using namespace std;


////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////


////////////////////////////////// 求最大整数  //////////////////////////////////
template<int a, int ...args>
struct IntMax;

template<int a>
struct IntMax<a> :std::integral_constant<int, a>
{

};

template<int a1, int a2, int ...args>
struct IntMax<a1, a2, args...> :std::integral_constant<int, (a1 >= a2) ? IntMax<a1, args...>::value : IntMax<a2, args...>::value>
{

};


////////////////////////////////// 求内存对齐  //////////////////////////////////
template<typename ...args>
struct MaxAlign :std::integral_constant<int, IntMax<std::alignment_of<args>::value...>::value>
{

};