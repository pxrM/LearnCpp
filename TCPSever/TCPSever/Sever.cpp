#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	WSADATA WsaData;
	//1.初始化socket库
	if (WSAStartup(MAKEWORD(4, 3), &WsaData) != 0)
	{
		return -1;
	}
	//2.创建socket	AF_INET(IPV4)	AF_INET6(IPV6)
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "创建失败" << endl;
		WSACleanup();
		return -1;
	}
	//3.设置ip和端口
	sockaddr_in SeverAddr;
	SeverAddr.sin_family = AF_INET;
	SeverAddr.sin_port = htons(66006);
	SeverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	//任意地址
	//4.绑定地址
	if (bind(ListenSocket, (SOCKADDR*)&SeverAddr, sizeof(SeverAddr)) == SOCKET_ERROR) 
	{
		cout << "绑定失败" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	//5.启动监听（有没有人请求链接）
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		cout << "监听失败" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	//6.创建链接进来的客户端地址信息
	sockaddr_in ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	cout << "等待链接.." << endl;
	//7.服务器接受客户端的链接
	SOCKET RevSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen);
	if (RevSocket == INVALID_SOCKET)
	{
		cout << "客户端发出请求，服务端接收失败" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	else {
		cout << "客户端发出请求，服务端接收成功" << endl;
		cout << "客户端地址：" << inet_ntoa(ClientAddr.sin_addr) << endl;	
		cout << "客户端端口：" << ClientAddr.sin_port << endl;
	}
	//8.接收客户端信息
	char BufData[1024] = { 0 };
	int Res = recv(RevSocket, BufData, 1024, 0);
	if (Res == 0)
	{
		cout << "链接关闭" << endl;
	}
	else if(Res > 0)
	{
		cout << "客户端发送的数据是：" << BufData << endl;
		cout << "客户端发送的数据大小是：" << Res << endl;
	}
	else
	{
		cout << "接收失败：" << WSAGetLastError() << endl;
	}
	//9.给客户端回信息'
	memset(BufData, 0, 1024);
	strcpy(BufData, "Sever ···");
	send(RevSocket, BufData, strlen(BufData), 0);


	return 0;
}
