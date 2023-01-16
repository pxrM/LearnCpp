/*
				  Ա��
	��Ŀ��  ����  Ա��
				  Ա��
	����һ���������һ�����̣�����������һ�����̣߳��߳���Ҫ����һ��һ�е�ִ�д��룬
	������ʱ������̷߳���һ����ջ���ݣ�����ͨ��vs�Զ���������ڴ����߳�ʱ�Զ��壬
	�߳�֮���ǲ���ִ�еģ��������̣߳�

	����̲������ֲ�ʽ��������֮���ͨ�ŷ�ʽ socket�׽��֡������ļ��Ķ�д���ܵ����ź�

	Ӳ��������ͨ��cpu����ȥ�����̣߳�

	ͬ����1ִ��������ִ��2
	�첽��1��2һ��ִ��

	������ֹ����̷߳��ʹ�����Դ�������⣬������ʱ�����̲߳��ܷ��ʣ�����߳̽�������
	��������һ���̷߳�����Դʱ���м�������������߳̿�ס�ˣ�Ȼ�������Ŷӷ��ʵ��߳�Ҳ����ס��
	���������������Ƕ���߳�һ��ȥ�������������߳���ִ�У�û�����������߳���Ҫ�ȴ����Ȼ�����ʹ�����ͷź������ȴ����߳���ȥ���������

*/
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <Windows.h> //����ͻ����߳���Ҫ
#include <condition_variable> //������
#include <future>

using namespace std; //��ƽ̨


void Hello1()
{
	std::cout << "Hello1 thread" << std::endl;

	//std::this_thread::sleep_for(std::chrono::seconds(2));	//��ǰ�߳���������
}

void Hello2()
{
	std::cout << "Hello2 thread" << std::endl;
}

void Hello3(int a, string b)
{
	std::cout << a << b << std::endl;
}




std::mutex mtest;

// ������
void Hello4()
{
	mtest.lock();	//�̼߳���  �����߳̿�ʼ�����Ŷ�

	cout << "Hello4" << endl;
	this_thread::sleep_for(chrono::seconds(2));

	mtest.unlock();	//����		��������������ͻ�������������
}


// ��ƻ�����
struct MyEvent
{
	MyEvent()
	{
		m.lock();
	}

	~MyEvent()
	{
		m.unlock();
	}
	static mutex m;
};

mutex MyEvent::m;
#define LOCK MyEvent Event;

void Hello5()
{
	bool bLock = MyEvent::m.try_lock();	 // �����ǰ�߳�û�б�����ô�᷵��true ����ǰ�߳̿��Ա���

	if (bLock)
	{
		LOCK;

		cout << "Hello5" << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
}


void Hello6()
{
	while (true)
	{
		Sleep(1000);	//����һ�� ��window�ײ�api

		cout << "window sleep" << endl;
	}
}

void Hello7(string str)
{
	cout << "Hello7" << str << endl;
}

mutex mtest2;
void Hello8()
{
	std::lock_guard<mutex> lgm(mtest2);	//������ MyEvent
}

void Hello9()
{
	unique_lock<mutex> ugm(mtest2);	//������ MyEvent
	//unique_lock<mutex> gm(mtest2, chrono::seconds(2));
	//ugm.try_lock_for(chrono::seconds(2));	//������
	cout << "��δ��뱻��������" << endl;
	ugm.unlock();

	cout << "Hello9" << endl;
}

void Init()
{
	cout << "init" << endl;
	Sleep(2000);
}
once_flag o_flag;
void Hello10()
{
	cout << "Hello10" << endl;
	call_once(o_flag, []()
		{
			Init();	// �ڶ��̵߳��õ������ִֻ��һ��
		});
}

mutex mtest3;
condition_variable cv;
void Hello11()
{
	cout << "Hello11" << endl;
	Sleep(1000);
	if (true)
	{
		cv.notify_one();	//�������߳�
	}
}

string GetHello1(int a)
{
	cout << "GetHello1  " << a << endl;
	return "ok";
}

string GetHello2(future<string> &fu)
{
	cout << "GetHello2  " << fu.get() << endl;
	return "ok";
}

string GetHello3(shared_future<string> fu)
{
	cout << "GetHello3  " << fu.get() << endl;
	return "ok";
}

int GetHello4(int a, int b)
{
	return a + b;
}


HANDLE hMutex = nullptr;
DWORD WINAPI FuncThread1(LPVOID lpParam)
{
	cout << "FuncThread1" << endl;
	WaitForSingleObject(hMutex, INFINITE);
	Sleep(1000);
	ReleaseMutex(hMutex);
	return 01;
}



class CTest
{
public:
	void Run(const string &a)
	{
		cout << a << endl;
	}
};


int main()
{
	cout << "main enter" << endl;
	//std::thread threadTest1(Hello1);
	//std::thread threadTest2(Hello2);
	//threadTest2.swap(threadTest1);
	//threadTest2.join();
	//cout << "�߳�id=0��ʾ�̷߳ǻ�Ծ״̬ " << threadTest1.joinable() << endl;
	//cout << "thread id = " << threadTest1.get_id() << endl;
	//threadTest1.join();		//join���������߳� ͬ������
	////threadTest1.detach();	//������
	//cout << "Ӳ������������ ���Կ����ٸ��߳� = " << threadTest1.hardware_concurrency() << endl;
	////auto winHandle = threadTest1.native_handle();	//��ȡwin�ľ������һЩԭ������
	//std::thread threadTest3;
	//cout << "�߳�id=0��ʾ�̷߳ǻ�Ծ״̬ " << threadTest3.joinable() << endl;


	/*------------------------------*/

	//thread threadTest4(Hello3, 6, "can");
	//threadTest4.detach();
	//int test5 = 100;

	/*------------------------------*/

	//thread threadTest5([&](int a, string b) {
	//	cout << test5 << a << b << endl;
	//	}, 6, "test");
	//threadTest5.detach();

	/*------------------------------*/

	//CTest ct1;
	//thread threadTest6(&CTest::Run, &ct1, "ct1");
	////threadTest6.detach();

	////for (int i = 0; i < threadTest6.hardware_concurrency(); i++)
	////{
	////	thread threadTest7(Hello4);
	////	threadTest7.join();
	////}
	//for (int i = 0; i < threadTest6.hardware_concurrency(); i++)
	//{
	//	thread threadTest7(Hello5);
	//	threadTest7.join();
	//}

	/*------------------------------*/

	//thread threadTest8(Hello6);
	//SuspendThread(threadTest8.native_handle());	// �����߳�
	//this_thread::sleep_for(chrono::seconds(2));		//��ǰ�߳���������
	//ResumeThread(threadTest8.native_handle());	//�����߳�

	/*------------------------------*/

	//ʹ��move���Ա��⿽��
	//thread threadTest9(Hello7, move("����"));
	//thread threadTest10 = move(threadTest9);
	//threadTest10.join();

	/*------------------------------*/

	//thread threadTest11;
	//for (int i = 0; i < threadTest10.hardware_concurrency(); i++)
	//{
	//	thread threadTest11(Hello10);
	//	threadTest11.join();
	//}

	/*------------------------------*/

	//thread threadTest12(Hello11);
	//threadTest12.detach();


	//unique_lock<mutex> ulock(mtest3);
	//cv.wait(ulock);	// ��ס���߳�

	/*------------------------------*/

	//future<string> newfuture = async(launch::async, GetHello1, 8);
	//Sleep(2000);
	//if (newfuture.valid())	//�Ƿ���Ի�ȡ����ֵ	
	//{
	//	string re = newfuture.get();
	//	cout << re << endl;
	//}
	//// newfuture.get();  �ٴε��ûᱼ��

	/*------------------------------*/

	//promise<string> pro;
	////promise<string> pro1;
	////pro1 = move(pro);
	//future<string> fu1 = pro.get_future();
	//future<string> fu2 = async(launch::async, GetHello2, std::ref(fu1));
	//pro.set_value("�����̴߳�������������߳�");


	/*------------------------------*/
	//promise<string> pro2;
	//future<string> fu3 = pro2.get_future();
	//shared_future<string> shardfu = fu3.share();	//�����ŵ
	//future<string> fu4 = async(launch::async, GetHello3, shardfu);
	//future<string> fu5 = async(launch::async, GetHello3, shardfu);
	//pro2.set_value("�����̴߳�������������߳�");


	/*------------------------------*/
	////�첽���ð󶨵ĺ���
	//packaged_task<int(int, int)> ptask([](int a, int b)->int {
	//	return a + b;
	//});
	//bool bbind = ptask.valid();	//�Ƿ���˺���
	//ptask(1, 6);
	//auto fu6 = ptask.get_future();
	//cout << fu6.get() << endl;

	//packaged_task<int(int, int)> ptask1(GetHello4);
	//ptask1(6, 6);
	//auto fu7 = ptask1.get_future();
	//cout << fu7.get() << endl;

	//packaged_task<int(int, int)>ptask2(std::bind(GetHello4, 9, 8));
	//ptask2(1, 1);	//��������Ч��
	//auto fu8 = ptask2.get_future();
	//cout << fu8.get() << endl;



	/*------------------------------*/
	//ʱ��Լ��
	//������ʱ���������������
	thread threadTest13(Hello1);
	chrono::steady_clock::time_point timepos = chrono::steady_clock::now() + chrono::milliseconds(2000);
	this_thread::sleep_until(timepos);
	threadTest13.join();

	mutex mutex_m;
	unique_lock<mutex>unipl1(mutex_m);



	/*------------------------------*/
	//windows ���߳�
	//WINBASEAPI
	//	_Ret_maybenull_
	//	HANDLE
	//	WINAPI
	//	CreateThread(
	//		_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,	//���̰߳�ȫ��� һ��Ϊnull
	//		_In_ SIZE_T dwStackSize,	//�߳�ջ��С  0ΪĬ��
	//		_In_ LPTHREAD_START_ROUTINE lpStartAddress,		//���߳�ִ�еĻص�����
	//		_In_opt_ __drv_aliasesMem LPVOID lpParameter,		//�����̲߳���
	//		_In_ DWORD dwCreationFlags,		//�����̴߳�����һ����־  0=�������� CREATE_SUSPENDEN(0x00000004)
	//		_Out_opt_ LPDWORD lpThreadId		//�߳�id
	//	);

		//WINBASEAPI
	//	_Ret_maybenull_
	//	HANDLE
	//	WINAPI
	//	CreateMutexW(
	//		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	//���̰߳�ȫ��� һ��Ϊnull
	//		_In_ BOOL bInitialOwner,	//��û�и����Ŀ���Ȩ
	//		_In_opt_ LPCWSTR lpName		//������
	//	);

	HANDLE h1 = CreateThread(nullptr, 0, FuncThread1, nullptr, 0, nullptr);
	Sleep(2000);
	if (h1)
	{
		CloseHandle(h1);
	}


	hMutex = CreateMutex(nullptr, FALSE, L"HelloMutex");
	for (int i = 0; i < 10; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		Sleep(1000);

		if (hMutex)
		{
			ReleaseMutex(hMutex);
		}
	}
	
	


	cout << "main thread" << endl;

	this_thread::sleep_for(chrono::seconds(2));		//��ǰ�߳���������

	return 0;
}