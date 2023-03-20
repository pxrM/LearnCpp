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

	// ����socket
	bool bReuseAddr = true;
	int Ret = setsockopt(
		SocketServer,
		SOL_SOCKET,//��ǰ��socket
		SO_REUSEADDR,//һ����˵�˿��ͷź�Ҫ�������Ӳ����ٴ�ʹ�ã�����Ϊ�ͷź������ʹ��
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

	//��select���ӿͻ���
	fd_set _set;
	FD_ZERO(&_set);	//�����ڴ�
	FD_SET(SocketServer, &_set);
	SOCKET ClientSocket;
	sockaddr_in AddrClient;
	int AddrClientLen = sizeof(AddrClient);
	char Buffer[1024] = { 0 };
	while (true)
	{
		//select(
		//	_In_ int nfds,
		//	_Inout_opt_ fd_set FAR * readfds, //�ɶ���
		//	_Inout_opt_ fd_set FAR * writefds,	//��д��
		//	_Inout_opt_ fd_set FAR * exceptfds,	//������
		//	_In_opt_ const struct timeval FAR * timeout //���ȴ�ʱ��
		//);
		fd_set Lastfd = _set;
		Ret = select(0, &Lastfd, NULL, NULL, nullptr);
		if (Ret >= 0)
		{
			for (UINT i = 0; i < _set.fd_count; i++)
			{
				if (FD_ISSET(_set.fd_array[i], &Lastfd)) //�ж�socket�Ƿ���Ч
				{
					if (_set.fd_array[i] == SocketServer)
					{
						//���������
						memset(&AddrClient, 0, AddrClientLen);
						ClientSocket = accept(SocketServer, (sockaddr*)&AddrClient, &AddrClientLen);
						if (ClientSocket != INVALID_SOCKET)
						{
							FD_SET(ClientSocket, &_set);
							//ntohs �����ֽ��� תΪ �����ֽ���
							cout <<
								"һ���ͻ������ӽ�����" << ClientSocket <<
								"�˿ڣ�" << ntohs(AddrClient.sin_port) <<
								"��ַ��" << inet_ntoa(AddrClient.sin_addr) << endl;
						}
					}
					else
					{
						//���ܿͻ��˵���Ϣ
						memset(&Buffer, 0, 1024);
						Ret = recv(_set.fd_array[i], Buffer, 1024, 0);
						if (Ret == 0)
						{
							closesocket(_set.fd_array[i]);
							FD_CLR(_set.fd_array[i], &_set);
							cout << "�ͻ��������˳�" << endl;
							i--;
						}
						else if (Ret == SOCKET_ERROR)
						{
							closesocket(_set.fd_array[i]);
							FD_CLR(_set.fd_array[i], &_set);
							cout << "������Ϣ����" << endl;
							i--;
						}
						else
						{
							// ͨ��socket��ȡ��ַ
							getpeername(_set.fd_array[i], (sockaddr*)&AddrClient, &AddrClientLen);
							if (Ret > 0)
							{
								cout << "�˿ڣ�" << ntohs(AddrClient.sin_port)
									<< "IP��" << inet_ntoa(AddrClient.sin_addr)
									<< "Buffer��" << Buffer
									<< "BufferLen��" << Ret
									<< endl;

								memset(&Buffer, 0, 1024);
								strcpy(Buffer, "Server...");
								Ret = send(_set.fd_array[i], Buffer, strlen(Buffer), 0);
								if (Ret == SOCKET_ERROR)
								{
									cout << "����ʧ��" << endl;
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