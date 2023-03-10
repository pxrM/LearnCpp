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
	//
	SOCKADDR_IN Addr;
	Addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(98986);
	//
	bind(InSocket, (SOCKADDR*)&Addr, sizeof(SOCKADDR));
	// ¿Í»§¶ËµØÖ·
	SOCKADDR_IN AddrClient;
	int AddrClientLen = sizeof(SOCKADDR_IN);
	//
	char RecvBuffer[1024] = { 0 };
	recvfrom(InSocket, RecvBuffer, 1024, 0, (SOCKADDR*)&AddrClient, &AddrClientLen);
	printf(RecvBuffer);
	//
	memset(RecvBuffer, 0, 1024);
	sprintf_s(RecvBuffer, 1024, "Hi I'am Sever \n");
	sendto(InSocket, RecvBuffer, 1024, 0, (SOCKADDR*)&AddrClient, sizeof(SOCKADDR));
	//
	closesocket(InSocket);
	WSACleanup();


	return 0;
}