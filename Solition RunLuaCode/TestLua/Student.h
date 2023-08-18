#pragma once

#include <iostream>
#include <string>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std;


class Student
{
public:
	Student(int age, const string& name, int schoolNum, int classNum) :
		iAge(age), sName(name), iSchoolNum(schoolNum), iClassNum(classNum) 
	{
		cout << "Constructor Student" << endl;
	}
	~Student() { cout << "Destructor Student" << endl; }

	void SetAge(int age) { iAge = age; }
	const int GetAge() const { return iAge; }
	void SetName(const string& name) { sName = name; }
	const string& GetName()const { return sName; }

	virtual void ShowSelfInfo()
	{
		cout << "Age:" << iAge << "Name:" << sName << "School:" << iSchoolNum << "Class:" << iClassNum << endl;
	}

	
private:
	int iAge;
	string sName;
	int iSchoolNum;
	int iClassNum;
};
