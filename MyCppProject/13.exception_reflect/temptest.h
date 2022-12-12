#pragma once
#include <iostream>

using namespace std;

template<class T>
class TempAA
{
public:
	virtual void Init()
	{
		cout << "AA::Init" << endl;
	}
	virtual void Destroy()
	{
		cout << "AA::Destroy" << endl;
	}

	void Func(int a, int b)
	{

	}
	void Func(int a)
	{

	}

private:
	T *Data;
};


class TempBB :public TempAA<int>
{
	typedef TempAA<int> Super;
public:
	virtual void Init()
	{
		cout << "BB::Init" << endl;
	}
	virtual void Destroy()
	{
		cout << "BB::Destroy" << endl;
	}
private:

};

