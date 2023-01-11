/*
				  员工
	项目组  主程  员工
				  员工
	启动一个程序就是一个进程，进程至少有一个主线程，线程需要工作一行一行的执行代码，
	在运行时会给主线程分配一定的栈数据，可以通过vs自定义或者是在创建线程时自定义，
	线程之间是并行执行的（包括主线程）

	多进程并发（分布式），进程之间的通信方式 socket套接字、磁盘文件的读写、管道、信号

	硬件并发（通过cpu核数去开启线程）

	同步：1执行完了再执行2
	异步：1、2一起执行

	锁：防止多个线程访问共享资源出现问题，当加锁时其它线程不能访问，会对线程进行阻塞
	死锁：当一个线程访问资源时进行加锁，但是这个线程卡住了，然后其它排队访问的线程也都卡住了
	互斥锁：互斥锁是多个线程一起去抢，抢到锁的线程先执行，没有抢到锁的线程需要等待，等互斥锁使用完释放后，其它等待的线程再去抢这个锁。

*/
#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std; //跨平台


void Hello1()
{
	std::cout << "Hello1 thread" << std::endl;

	//std::this_thread::sleep_for(std::chrono::seconds(2));	//当前线程休眠两秒
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

// 互斥锁
void Hello4()
{
	mtest.lock();	//线程加锁  后面线程开始挂起排队

	cout << "Hello4" << endl;
	this_thread::sleep_for(chrono::seconds(2));

	mtest.unlock();	//解锁		这里如果不解锁就会出现死锁的情况
}


// 设计互斥锁
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
	cout << "线程id=0表示线程非活跃状态 " << threadTest1.joinable() << endl;
	cout << "thread id = " << threadTest1.get_id() << endl;
	threadTest1.join();		//join会阻塞主线程 同步操作
	//threadTest1.detach();	//非阻塞
	cout << "硬件并发的数量 可以开多少个线程 = " << threadTest1.hardware_concurrency() << endl;
	//auto winHandle = threadTest1.native_handle();	//获取win的句柄进行一些原生操作
	std::thread threadTest3;
	cout << "线程id=0表示线程非活跃状态 " << threadTest3.joinable() << endl;

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

	this_thread::sleep_for(chrono::seconds(2));		//当前线程休眠两秒

	return 0;
}