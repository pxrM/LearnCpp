/*
	����Э��
*/

#pragma once

#include <iostream>

using namespace std;

typedef unsigned char uint8;


//����������Ϣ����
template<uint8 MessageType> //��ӦЭ���
class NetControlMessage
{

};


//������Ϣ
class NetControlMessageInfo
{
public:
	// ������Ϣ����
	template<typename ... ParamTypes> //֧������ε�ģ��
	static void ReceiveParams(ParamTypes &... Params)
	{

	}

	// ������Ϣ����
	template<typename ... ParamTypes>
	static void SendParams(ParamTypes &... Params)
	{

	}
};

enum //ȫ��ö��
{
	ETest_A = 0,
};

/////////////////////////// ���ַ�ʽÿ����һ��Э��Ŷ���Ҫ����һ��ģ�� ///////////////////////////
/*
template<> class NetControlMessage<0>
{
public:
	template<typename ...ParamTypes>
	static void Receive(ParamTypes &... Params)
	{
		NetControlMessageInfo::ReceiveParams(Params...);
	}

	template<typename ...ParamTypes>
	static void Send(ParamTypes &... Params)
	{
		NetControlMessageInfo::SendParams(Params...)
	}
};
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_CONTROL_CHANNEL_MESSAGE(Name, Index, ...) \
enum \
{ \
	NMT_##Name = Index, \
}; \
template<> class NetControlMessage<Index> \
{ \
public: \
	template<typename ...ParamTypes> \
	static void Receive(ParamTypes &... Params) \
	{ \
		NetControlMessageInfo::ReceiveParams(Params...); \
	} \
	template<typename ...ParamTypes> \
	static void Send(ParamTypes &... Params) \
	{ \
		NetControlMessageInfo::SendParams(Params...); \
	} \
};

//����Э����Ϊ
DEFINE_CONTROL_CHANNEL_MESSAGE(Enter, 0, int, float, char)
DEFINE_CONTROL_CHANNEL_MESSAGE(Login, 1, int, char)





/////////////////////////// ��������Σ�չ����ʽ�� ///////////////////////////
template<typename T>
void PrintfArg(T &arg)
{
	cout << arg << endl;
}

template<typename ... ParamTypes>
void FunTest(ParamTypes &... Params)
{
	// std::forward()
	char arr[] = { (PrintfArg(Params), 0)... }; //����0��ʾռλ��������PrintfArg�����Ӹ�����ֵ�����ַ�ʽ���������
	char arr2[] = { (char)Params ... };
}

/////////////////////////// ��������Σ��ݹ鷽ʽ�� ///////////////////////////
void FunTest2()
{
	cout << "û����" << endl;
}
template<typename T, typename ... ParamTypes>
void FunTest2(T &Head, ParamTypes &... Params)
{
	cout << "Head = " << Head << endl;
	FunTest2(Params...);
}

/////////////////////////// ��ȡ�ɱ���������� ///////////////////////////
template<typename ... ParamTypes>
void FunTestLen(ParamTypes &... Params)
{
	cout << sizeof...(Params) << endl;
}

/////////////////////////// ͨ���ɱ����������� ///////////////////////////
template <typename ParamTypes>
ParamTypes &FuncValue(ParamTypes &Param)
{
	return Param;
}
template<typename T, typename ... ParamTypes>
T FuncValue(T &Head, ParamTypes &... Params)
{
	return Head + FuncValue<T>(Params...);
}

/////////////////////////// ʲô��ģ�巺������ǰ����ģ�������δ���壬ֻ�еȵ�ʹ�õ�ʱ��֪�� ///////////////////////////
template<class T1, class T2>
class TempTest_Two
{
private:
	T1 Data1;
	T2 Data2;
};

/////////////////////////// ʲô��ģ��ȫ�ػ�������һ��ȷ�������ͣ�ǰ����Ҫ�и�������ģ�� ///////////////////////////
template<>
class TempTest_Two<int, float>
{
};

template<class T>
void FuncTempTest()
{
}

template<>
void FuncTempTest<int>(){}

/////////////////////////// ģ��ƫ�ػ�������û��ƫ�ػ��� ///////////////////////////
//ͨ��ģ��ƫ�ػ�����ȡ�ɱ�������ֽڴ�С
template<typename T, class ...ParamTypes>
class TempTestLen
{
public:
	enum
	{
		Num = TempTestLen<T>::Num + TempTestLen<ParamTypes...>::Num,
	};
};

//ƫ�ػ�
template<typename Last>
class TempTestLen<Last>
{
public:
	enum
	{
		Num = sizeof(Last),
	};
}; 

#define TEMP_TEST_LEN(Name, ...) TempTestLen<__VA_ARGS__> Name

/////////////////////////// ͨ��ģ��ѭ���̳з�ʽչ���ɱ���� ///////////////////////////
template<int ...>
struct HelloIndex
{

};

template<int N, int...ParamTypes>
struct SpawnIndex :SpawnIndex<N - 1, N - 1, ParamTypes...>
{

};

template<int...ParamTypes>
struct SpawnIndex<0, ParamTypes...>
{
	typedef HelloIndex<ParamTypes...> MType;
};

