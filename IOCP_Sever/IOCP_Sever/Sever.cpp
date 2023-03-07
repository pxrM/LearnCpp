#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <process.h>	//����
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


struct IOData
{
	IOData()
	{
		ZeroMemory(this, sizeof(IOData));	//��ʼ���Լ�
	}

	OVERLAPPED OverL;	//�ص�io
	CHAR Buffer[1024];
	BYTE Type;	//���� ��ȡ����д��
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
	DWORD Len = 0;	//�����˶���
	DWORD Flag = 0;
	Data.Type = 0;
	Data.WsaBuf.buf = Data.Buffer;
	Data.WsaBuf.len = 1024;
	if (WSARecv(ClientSocket, &Data.WsaBuf, 1, &Len, &Flag, &Data.OverL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == ERROR_IO_PENDING)	//��Ϣ��δ�������
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL ClientObj::Send()
{
	DWORD Len = 0L;
	DWORD Flag = 0L;
	Data.Type = 1;
	Data.WsaBuf.buf = Data.Buffer;
	Data.WsaBuf.len = strlen(Data.Buffer);
	if (WSASend(ClientSocket, &Data.WsaBuf, 1, &Len, Flag, (LPOVERLAPPED)&Data.OverL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == ERROR_IO_PENDING)	//��Ϣ��δ�������
		{
			return FALSE;
		}
	}
	return TRUE;
}

//���ӽ����Ŀͻ���
list<ClientObj*>ClientList;

// ��ɶ˿�
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

//�����߳�
unsigned int __stdcall Run(void* content)
{
	for (;;)
	{
		Sleep(1000);
		DWORD IOSize = -1;	//���һ��io����������ֽ����Ƕ���
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
			// ��ȡ����
			IOData* pData = CONTAINING_RECORD(lpOverlapped, IOData, OverL);
			switch (pData->Type)
			{
			case 0:	//���յ��˿ͻ��˷��͹�������Ϣ
			{
				Client->Data.Len = IOSize;
				Client->Data.Buffer[IOSize] = '\0';
				printf(Client->Data.Buffer);

				char buffer[1024] = { 0 };
				sprintf_s(buffer, 1024, "hi I'am Sever %d \n", Client->ClientSocket);
				strcpy(Client->Data.Buffer, buffer);
				Client->Send();
				break;
			}
			case 1:
			{
				printf(Client->Data.Buffer);
				Client->Data.Len = 0;
				if (!Client->Recv())
				{
					RemoveClientList(Client);
				}
				break;
			}
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
	// �̵߳ķ��ؾ��
	HANDLE hThreadHandle[32];

	// ������ɶ˿�
	Cp = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE, //�򿪵��ļ���� ����ʹ����Чֵ
		NULL, //���е�io��ɶ˿�
		0,
		0);
	if (Cp == NULL)
	{
		// ������ ��ȡ������Ϣ
		//GetLastError();
		printf("������ɶ˿�ʧ��");
		return -1;
	}

	//SYSTEM_INFO ��ȡϵͳ��Ϣ
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD CPUNum = SystemInfo.dwNumberOfProcessors;	//cpu����

	for (int i = 0; i < CPUNum * 2; ++i)
	{
		hThreadHandle[i] = (HANDLE)_beginthreadex(
			NULL,//��ȫ���ԣ�ΪNULLʱ��ʾĬ�ϰ�ȫ����
			0,	 //�̵߳Ķ�ջ��С������0ΪĬ�ϴ�С
			Run, //�̵߳���������
			Cp,	 //�̺߳�������
			0,	 //�̵߳ĳ�ʼ״̬��0��ʾ����ִ�У�CREATE_SUSPENODE��ʾ���������
			NULL //�����߳�id
		);
	}

	WSADATA WsaData;
	int Ret = WSAStartup(
		MAKEWORD(2, 1), //ָ���汾������һ�����ֽ� ָ�����汾�������������ֽ� ָ���޶���
		&WsaData);
	if (Ret != 0)
	{
		return -1;
	}

	// ����socket
	SOCKET Listen = WSASocket(
		AF_INET,	 //��ַ��
		SOCK_STREAM, //TCP  SOCK_DGRAM UDP
		0,			 //Э��
		NULL,		 //�����׽�����Ч�Ľṹ ����nullĬ��
		0,
		WSA_FLAG_OVERLAPPED
	);
	if (Listen == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}

	// �󶨵�ַ
	SOCKADDR_IN Sin;
	Sin.sin_family = AF_INET;	//IPV4������Э����
	Sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//0.0.0.0 �����ַ 
	Sin.sin_port = htons(98986);//�������ֽ���תΪ�����ֽ���

	// socket �󶨵�ַ
	if (bind(Listen, (SOCKADDR*)&Sin, sizeof(Sin)) == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}

	// ��ʼ������û���ⲿ����
	if (listen(Listen, SOMAXCONN))
	{
		closesocket(Listen);
		WSACleanup();
		return -1;
	}

	// iocp��Ͷ��  �鿴��û�пͻ������ӽ���
	SOCKET ClientAccept = INVALID_SOCKET;
	SOCKADDR_IN	ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	for (;;)
	{
		// ��ʼ�������ȴ��ͻ�������
		ClientAccept = WSAAccept(
			Listen,//�������׽���
			(SOCKADDR*)&ClientAddr,//�ͻ��˵�ַ
			&ClientAddrLen,
			NULL,//�û��ṩ���������Ľ���ʵ�ʵ�ַ
			0);	//0����Ϊ�����������ظ����ó����һ������
		if (ClientAccept == SOCKET_ERROR)
		{
			break;
		}

		ClientObj* InClient = new ClientObj(ClientAccept, ClientAddr);
		ClientList.push_back(InClient);

		//�ѽ��յĿͻ��˰󶨵���ɶ˿�
		if (CreateIoCompletionPort(
			(HANDLE)ClientAccept,
			Cp,
			(DWORD)InClient,
			0) == NULL)
		{
			break;
		}

		if (!InClient->Recv())
		{
			RemoveClientList(InClient);
		}

	}


	return 0;
}