#include <iostream>
#include <list>
#include <process.h>	//进程
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


struct IOData
{
	OVERLAPPED OverL;	//重叠io
	CHAR Buffer[1024];
	BYTE Type;	//类型 读取还是写入
	DWORD Len; 
	WSABUF WsaBuf;
};

class ClientObj
{
public:
	ClientObj(SOCKET s, SOCKADDR_IN sin)
		:ClientSocket(s)
		, Sin(sin)
	{
	}

	~ClientObj()
	{
	}

public:
	BOOL Recv();
	BOOL Send();

public:
	SOCKET ClientSocket;
	SOCKADDR_IN Sin;
	IOData Data;
};

BOOL ClientObj::Recv()
{
	return TRUE;
}

BOOL ClientObj::Send()
{
	return TRUE;
}

//链接进来的客户端
list<ClientObj*>ClientList;

// 完成端口
HANDLE Cp = NULL;

void RemoveClientList(ClientObj* InC)
{
	for (list<ClientObj*>::iterator iter = ClientList.begin(); iter != ClientList.end(); ++iter)
	{
		if (InC == (*iter))
		{
			ClientList.erase(iter);
			break;
		}
	}
}

//工作线程
unsigned int __stdcall Run(void* content)
{
	for (;;)
	{
		Sleep(1000);
		DWORD IOSize = -1;	//完成一次io操作传输的字节数是多少

		LPOVERLAPPED lpOverlapped = NULL;
		ClientObj* Client = NULL;
		bool Ret = GetQueuedCompletionStatus(Cp, &IOSize, (PULONG_PTR)&Client, &lpOverlapped, INFINITE);

		if (Client == NULL && lpOverlapped == NULL)
		{
			break;
		}

		if (Ret)
		{
			if (IOSize == 0)
			{
				RemoveClientList(Client);
				continue;
			}
			// 提取数据
			IOData* pData = CONTAINING_RECORD(lpOverlapped, IOData, OverL);
			switch (pData->Type)
			{
			case 0:

				break;
			case 1:

				break;
			default:
				break;
			}
		}
		else
		{
			DWORD Msg = GetLastError();
			if (Msg == WAIT_TIMEOUT)
			{
				continue;
			}
			else if (lpOverlapped != NULL)
			{
				RemoveClientList(Client);
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}

int main()
{
	// 线程的返回句柄
	HANDLE hThreadHandle[32];

	// 创建完成端口
	Cp = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE, //打开的文件句柄 这里使用无效值
		NULL, //现有的io完成端口
		0,
		0);
	if (Cp == NULL)
	{
		// 出错了 获取错误信息
		//GetLastError();
		printf("创建完成端口失败");
		return -1;
	}

	//SYSTEM_INFO 获取系统信息
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD CPUNum = SystemInfo.dwNumberOfProcessors;	//cpu数量

	for (int i = 0; i < CPUNum * 2; ++i)
	{
		hThreadHandle[i] = (HANDLE)_beginthreadex(
			NULL,//安全属性，为NULL时表示默认安全属性
			0,	 //线程的堆栈大小，设置0为默认大小
			Run, //线程的启动函数
			Cp,	 //线程函数参数
			0,	 //线程的初始状态，0表示立即执行，CREATE_SUSPENODE表示创建后挂起
			NULL //接收线程id
		);
	}

	WSADATA WsaData;
	int Ret = WSAStartup(
		MAKEWORD(2, 1), //指定版本，参数一：低字节 指定主版本，参数二：高字节 指定修订版
		&WsaData);
	if (Ret != 0)
	{
		return -1;
	}

	// 创建socket
	SOCKET Listen = WSASocket(
		AF_INET,	 //地址族
		SOCK_STREAM, //TCP  SOCK_DGRAM UDP
		0,			 //协议
		NULL,		 //创建套接字特效的结构 这里null默认
		0,
		WSA_FLAG_OVERLAPPED
	);
	if (Listen == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}

	// 绑定地址
	SOCKADDR_IN Sin;
	Sin.sin_family = AF_INET;	//IPV4互联网协议族
	Sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//0.0.0.0 任意地址 
	Sin.sin_port = htons(98986);//将主机字节序转为网络字节序

	// socket 绑定地址
	if (bind(Listen, (SOCKADDR*)&Sin, sizeof(Sin)) == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}

	// 开始监听有没有外部访问
	if (listen(Listen, SOMAXCONN))
	{
		closesocket(Listen);
		WSACleanup();
		return -1;
	}

	// iocp的投递
	SOCKET ClientAccept = INVALID_SOCKET;
	SOCKADDR_IN	ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	for (;;)
	{
		// 开始阻塞，等待客户端链接
		ClientAccept = WSAAccept(
			Listen,//本机的套接字
			(SOCKADDR*)&ClientAddr,//客户端地址
			&ClientAddrLen,
			NULL,//用户提供条件函数的进程实际地址
			0);	//0：作为条件函数返回给引用程序的一个数据
		if (ClientAccept == SOCKET_ERROR)
		{
			break;
		}

		ClientObj* InClient = new ClientObj(ClientAccept, ClientAddr);
		ClientList.push_back(InClient);

		//绑定完成端口
		if (CreateIoCompletionPort(
			(HANDLE)ClientAccept,
			Cp,
			(DWORD)InClient,
			0) == NULL)
		{
			break;
		}
	}


	return 0;
}