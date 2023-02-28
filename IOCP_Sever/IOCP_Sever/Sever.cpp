#include <list>
#include <process.h>	//����
#include <winnt.h>
#include <winsock.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

//�����߳�
unsigned int __stdcall Run(void* content)
{

}

// ��ɶ˿�
HANDLE Cp = NULL;

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
	GetSystemInfo(SystemInfo);
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

	// ��ʼ����
	if (listen(Listen, SOMAXCONN))
	{
		closesocket(Listen);
		WSACleanup();
		return -1;
	}

	return 0;
}