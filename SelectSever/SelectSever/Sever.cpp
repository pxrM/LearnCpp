#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA WsaData;
	WSAStartup(WINSOCK_VERSION, &WsaData);

	SOCKET SocketServer = socket(AF_INET, SOCK_STREAM, 0);

	if (SocketServer == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(66006);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 设置socket
	bool bReuseAddr = true;
	int Ret = setsockopt(
		SocketServer,
		SOL_SOCKET,//当前的socket
		SO_REUSEADDR,//一般来说端口释放后要等两分钟才能再次使用，这里为释放后立马可使用
		(char*)&bReuseAddr,
		sizeof(bReuseAddr)
	);
	if (Ret == SOCKET_ERROR)
	{
		closesocket(SocketServer);
		WSACleanup();
		return -1;
	}

	Ret = bind(SocketServer, (sockaddr*)&addrServer, sizeof(addrServer));
	if (Ret == SOCKET_ERROR)
	{
		closesocket(SocketServer);
		WSACleanup();
		return -1;
	}

	Ret = listen(SocketServer, 5);
	if (Ret == SOCKET_ERROR)
	{
		closesocket(SocketServer);
		WSACleanup();
		return -1;
	}

	//用select链接客户端
	fd_set _set;
	FD_ZERO(&_set);	//清理内存
	FD_SET(SocketServer, &_set);
	SOCKET ClientSocket;
	sockaddr_in AddrClient;
	int AddrClientLen = sizeof(AddrClient);
	char Buffer[1024] = { 0 };
	while (true)
	{
		//select(
		//	_In_ int nfds,
		//	_Inout_opt_ fd_set FAR * readfds, //可读性
		//	_Inout_opt_ fd_set FAR * writefds,	//可写性
		//	_Inout_opt_ fd_set FAR * exceptfds,	//错误检测
		//	_In_opt_ const struct timeval FAR * timeout //最多等待时间
		//);
		fd_set Lastfd = _set;
		Ret = select(0, &Lastfd, NULL, NULL, nullptr);
		if (Ret >= 0)
		{
			for (UINT i = 0; i < _set.fd_count; i++)
			{
				if (FD_ISSET(_set.fd_array[i], &Lastfd)) //判断socket是否有效
				{
					if (_set.fd_array[i] == SocketServer)
					{
						//处理服务器
						memset(&AddrClient, 0, AddrClientLen);
						ClientSocket = accept(SocketServer, (sockaddr*)&AddrClient, &AddrClientLen);
						if (ClientSocket != INVALID_SOCKET)
						{
							FD_SET(ClientSocket, &_set);
							//ntohs 网络字节序 转为 主机字节序
							cout <<
								"一个客户端链接进来：" << ClientSocket <<
								"端口：" << ntohs(AddrClient.sin_port) <<
								"地址：" << inet_ntoa(AddrClient.sin_addr) << endl;
						}
					}
					else
					{
						//接受客户端的信息
						memset(&Buffer, 0, 1024);
						Ret = recv(_set.fd_array[i], Buffer, 1024, 0);
						if (Ret == 0)
						{
							closesocket(_set.fd_array[i]);
							FD_CLR(_set.fd_array[i], &_set);
							cout << "客户端正常退出" << endl;
							i--;
						}
						else if (Ret == SOCKET_ERROR)
						{
							closesocket(_set.fd_array[i]);
							FD_CLR(_set.fd_array[i], &_set);
							cout << "接收信息错误" << endl;
							i--;
						}
						else
						{
							// 通过socket获取地址
							getpeername(_set.fd_array[i], (sockaddr*)&AddrClient, &AddrClientLen);
							if (Ret > 0)
							{
								cout << "端口：" << ntohs(AddrClient.sin_port)
									<< "IP：" << inet_ntoa(AddrClient.sin_addr)
									<< "Buffer：" << Buffer
									<< "BufferLen：" << Ret
									<< endl;

								memset(&Buffer, 0, 1024);
								strcpy(Buffer, "Server...");
								Ret = send(_set.fd_array[i], Buffer, strlen(Buffer), 0);
								if (Ret == SOCKET_ERROR)
								{
									cout << "发送失败" << endl;
									closesocket(_set.fd_array[i]);
									continue;
								}
							}
						}
					}
				}
			}
		}
		else if (Ret == SOCKET_ERROR)
		{
			closesocket(SocketServer);
			WSACleanup();
			return -1;
		}
	}


	return 0;
}