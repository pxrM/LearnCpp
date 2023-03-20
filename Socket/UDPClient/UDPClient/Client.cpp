#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


using namespace std;

int main()
{
	//
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 1), &wsaData);
	if (ret != 0)
	{
		return -1;
	}
	//
	SOCKET InSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN Addr;
	Addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(98986);

	sendto(InSocket, "Hi I' am client", strlen("Hi I' am client"), 0, (SOCKADDR*)&Addr, sizeof(SOCKADDR));

	int Len = sizeof(SOCKADDR);
	char buffer[1024] = { 0 };

	recvfrom(InSocket, buffer, 1024, 0, (SOCKADDR*)&Addr, &Len); 
	printf(buffer);

	closesocket(InSocket);
	WSACleanup();


	return 0;
}