/*
	����Э��
*/

#pragma once


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