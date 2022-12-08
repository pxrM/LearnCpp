/*
	网络协议
*/

#pragma once


typedef unsigned char uint8;


//负责网络消息的类
template<uint8 MessageType> //对应协议号
class NetControlMessage
{

};


//网络信息
class NetControlMessageInfo
{
public:
	// 接受消息函数
	template<typename ... ParamTypes> //支持任意参的模板
	static void ReceiveParams(ParamTypes &... Params)
	{

	}

	// 发送消息函数
	template<typename ... ParamTypes>
	static void SendParams(ParamTypes &... Params)
	{

	}
};

enum //全局枚举
{
	ETest_A = 0,
};

/////////////////////////// 这种方式每增加一个协议号都需要增加一个模板 ///////////////////////////
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

//定义协议行为
DEFINE_CONTROL_CHANNEL_MESSAGE(Enter, 0, int, float, char)
DEFINE_CONTROL_CHANNEL_MESSAGE(Login, 1, int, char)