#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")



int main()
{
	WSADATA WsaData;
	int Ret = WSAStartup(
		MAKEWORD(2, 1), //指定版本，参数一：低字节 指定主版本，参数二：高字节 指定修订版
		&WsaData);
	if (Ret != 0)
	{
		return -1;
	}

	for (;;)
	{
		SOCKET ClientSocket = socket(
			AF_INET,
			SOCK_STREAM,
			IPPROTO_TCP
		);

		SOCKADDR_IN Sin;
		Sin.sin_family = AF_INET;
		Sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //设置服务端ip地址
		Sin.sin_port = htons(98986);	//设置服务端端口

		if (connect(
			ClientSocket,
			(SOCKADDR*)&Sin,
			sizeof(Sin)) == SOCKET_ERROR)
		{
			closesocket(ClientSocket);
			break;
		}

		//发报文
		char buffer[1024] = { 0 };
		sprintf_s(buffer, 1024, "Hello I'am client %d \n", ClientSocket);
		send(ClientSocket, buffer, strlen(buffer), 0);

		//接收
		memset(buffer, 0, 1024);
		recv(ClientSocket, buffer, sizeof(buffer), 0);

		printf(buffer);

		closesocket(ClientSocket);
	}

	WSACleanup();

	return 0;
}