#include <list>
#include <process.h>	//进程
#include <winnt.h>
#include <winsock.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

//工作线程
unsigned int __stdcall Run(void* content)
{

}

// 完成端口
HANDLE Cp = NULL;

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
	GetSystemInfo(SystemInfo);
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

	// 开始监听
	if (listen(Listen, SOMAXCONN))
	{
		closesocket(Listen);
		WSACleanup();
		return -1;
	}

	return 0;
}