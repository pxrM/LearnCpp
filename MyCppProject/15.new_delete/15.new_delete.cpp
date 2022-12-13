/*
	��̬�ڴ�
*/

#include <iostream>

using namespace std;


struct MyObj
{
public:
	MyObj()
	{
		cout << "MyObj ����" << endl;
	}

	virtual ~MyObj()
	{
		cout << "MyObj ����" << endl;
	}
};

struct MyObj2 :public MyObj
{
public:
	MyObj2()
	{
		cout << "MyObj2 ����" << endl;
	}

	~MyObj2()
	{
		cout << "MyObj2 ����" << endl;
	}
};



class MyObj3
{
public:
	MyObj3()
	{
		cout << "MyObj3 ����" << endl;
	}

	~MyObj3()
	{
		cout << "MyObj3 ����" << endl;
	}
};

class MyObj4 :public MyObj3
{
public:
	MyObj4()
	{
		cout << "MyObj4 ����" << endl;
	}

	~MyObj4()
	{
		cout << "MyObj4 ����" << endl;
	}
};


template<class T>
class PreDistribution
{
public:
	PreDistribution(int count) :Len(count)
	{
		Data = new T[count];
	}

	~PreDistribution()
	{
		delete[] Data;
	}

	T *operator[](int index)
	{
		return &Data[index];
	}

	inline int GetLen()
	{
		return Len;
	}

private:
	T *Data;
	int Len;
};


int main()
{
	// malloc �� free ֻ�Ƿ�����ͷ��ڴ�(������ù���������������ֶ���Ĭ�Ϲ�����Ϊ�ڴ��ʱ�Ѿ����䣬�����ֶ���������)
	MyObj *mo1 = (MyObj *)malloc(sizeof(MyObj));
	free(mo1);

	cout << "--------------------" << endl;

	// new �� delete ��������ʵ�ֹ������������
	MyObj *mo2 = new MyObj();
	delete mo2;

	cout << "--------------------" << endl;

	MyObj2 *mo21 = new MyObj2();
	delete mo21;

	cout << "--------------------" << endl;

	MyObj4 *mo41 = new MyObj4();
	delete mo41;

	cout << "--------------------" << endl;

	char *one = new char[1024];
	delete[] one;

	//��ά����
	int **two = new int *[1024];
	for (unsigned int i = 0; i < 1024; i++)
	{
		two[i] = new int[10];
	}
	for (unsigned int i = 0; i < 1024; i++)
	{
		delete[] two[i];
	}
	delete[] two;

	//��ά����
	int ***three = new int **[1024];
	for (unsigned int i = 0; i < 1024; i++)
	{
		three[i] = new int *[10];
		for (unsigned int j = 0; j < 10; j++)
		{
			three[i][j] = new int[10];
		}
	}
	for (unsigned int i = 0; i < 1024; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			delete[] three[i][j];
		}
		delete[] three[i];
	}
	delete[] three;



	PreDistribution<MyObj> pre(1024);
	MyObj *momo = pre[10];

	return 0;
}