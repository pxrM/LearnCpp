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
	LOCK;

	cout << "Hello5" << endl;
	this_thread::sleep_for(chrono::seconds(2));
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
	std::thread threadTest1(Hello1);
	std::thread threadTest2(Hello2);
	threadTest2.swap(threadTest1);
	threadTest2.join();
	cout << "�߳�id=0��ʾ�̷߳ǻ�Ծ״̬ " << threadTest1.joinable() << endl;
	cout << "thread id = " << threadTest1.get_id() << endl;
	threadTest1.join();		//join���������߳� ͬ������
	//threadTest1.detach();	//������
	cout << "Ӳ������������ ���Կ����ٸ��߳� = " << threadTest1.hardware_concurrency() << endl;
	//auto winHandle = threadTest1.native_handle();	//��ȡwin�ľ������һЩԭ������
	std::thread threadTest3;
	cout << "�߳�id=0��ʾ�̷߳ǻ�Ծ״̬ " << threadTest3.joinable() << endl;

	thread threadTest4(Hello3, 6, "can");
	threadTest4.detach();
	int test5 = 100;

	thread threadTest5([&](int a, string b) {
		cout << test5 << a << b << endl;
		}, 6, "test");
	threadTest5.detach();

	CTest ct1;
	thread threadTest6(&CTest::Run, &ct1, "ct1");
	//threadTest6.detach();

	//for (int i = 0; i < threadTest6.hardware_concurrency(); i++)
	//{
	//	thread threadTest7(Hello4);
	//	threadTest7.join();
	//}
	for (int i = 0; i < threadTest6.hardware_concurrency(); i++)
	{
		thread threadTest7(Hello5);
		threadTest7.join();
	}



	cout << "main thread" << endl;

	this_thread::sleep_for(chrono::seconds(2));		//��ǰ�߳���������

	return 0;
}