#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	WSADATA WsaData;
	//1.��ʼ��socket��
	if (WSAStartup(MAKEWORD(4, 3), &WsaData) != 0)
	{
		return -1;
	}
	//2.����socket	AF_INET(IPV4)	AF_INET6(IPV6)
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "����ʧ��" << endl;
		WSACleanup();
		return -1;
	}
	//3.����ip�Ͷ˿�
	sockaddr_in SeverAddr;
	SeverAddr.sin_family = AF_INET;
	SeverAddr.sin_port = htons(66006);
	SeverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	//�����ַ
	//4.�󶨵�ַ
	if (bind(ListenSocket, (SOCKADDR*)&SeverAddr, sizeof(SeverAddr)) == SOCKET_ERROR) 
	{
		cout << "��ʧ��" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	//5.������������û�����������ӣ�
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		cout << "����ʧ��" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	//6.�������ӽ����Ŀͻ��˵�ַ��Ϣ
	sockaddr_in ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	cout << "�ȴ�����.." << endl;
	//7.���������ܿͻ��˵�����
	SOCKET RevSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen);
	if (RevSocket == INVALID_SOCKET)
	{
		cout << "�ͻ��˷������󣬷���˽���ʧ��" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}
	else {
		cout << "�ͻ��˷������󣬷���˽��ճɹ�" << endl;
		cout << "�ͻ��˵�ַ��" << inet_ntoa(ClientAddr.sin_addr) << endl;	
		cout << "�ͻ��˶˿ڣ�" << ClientAddr.sin_port << endl;
	}
	//8.���տͻ�����Ϣ
	char BufData[1024] = { 0 };
	int Res = recv(RevSocket, BufData, 1024, 0);
	if (Res == 0)
	{
		cout << "���ӹر�" << endl;
	}
	else if(Res > 0)
	{
		cout << "�ͻ��˷��͵������ǣ�" << BufData << endl;
		cout << "�ͻ��˷��͵����ݴ�С�ǣ�" << Res << endl;
	}
	else
	{
		cout << "����ʧ�ܣ�" << WSAGetLastError() << endl;
	}
	//9.���ͻ��˻���Ϣ'
	memset(BufData, 0, 1024);
	strcpy(BufData, "Sever ������");
	send(RevSocket, BufData, strlen(BufData), 0);


	return 0;
}
