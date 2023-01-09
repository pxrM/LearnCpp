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

*/
#include <iostream>
#include <thread>
#include <string>

using namespace std; //��ƽ̨


void Hello1()
{
	std::cout << "Hello1 thread" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(2));	//��ǰ�߳���������
}

void Hello2()
{
	std::cout << "Hello2 thread" << std::endl;
}

void Hello3(int a, string b)
{
	std::cout << a << b << std::endl;
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
	cout << endl;
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
	threadTest6.detach();


	cout << "main thread" << endl;

	this_thread::sleep_for(chrono::seconds(2));

	return 0;
}