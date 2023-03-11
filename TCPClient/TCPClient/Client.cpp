#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	WSADATA WsaData;
	if (WSAStartup(MAKEWORD(4, 3), &WsaData) != 0)
	{
		return -1;
	}

	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "创建失败" << endl;
		WSACleanup();
		return -1;
	}

	sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(66006);
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (connect(ClientSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "请求链接失败：" << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}
	cout << "连接成功" << endl;

	char BufData[1024] = { 0 };
	strcpy(BufData, "I Client");

	int Res = send(ClientSocket, BufData, strlen(BufData), 0);
	if (Res == SOCKET_ERROR)
	{
		cout << "发送失败" << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}
	cout << "发送成功" << endl;

	memset(BufData, 0, 1024);
	Res = recv(ClientSocket, BufData, sizeof(BufData), 0);
	if (Res == 0)
	{
		cout << "链接关闭" << endl;
	}
	else if (Res > 0)
	{
		cout << "服务端发送的数据是：" << BufData << endl;
		cout << "服务端发送的数据大小是：" << Res << endl;
	}
	else
	{
		cout << "接收失败：" << WSAGetLastError() << endl;
	}


	return 0;
}