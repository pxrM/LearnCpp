/*
	·lambda
*/

#include <iostream>

using namespace std;


class TestA
{
public:
	TestA();
	void Init();

private:
	int a;
	int b;
	float ff;
};

TestA::TestA()
{
	a = 99;
	b = 16;
	ff = 1.6;
}

void TestA::Init()
{
	auto Func = [&]()
	{
		cout << a << endl;
	};

	auto Func1 = [&]()->bool
	{
		return true;
	};

	Func();
	bool b = Func1();
	if (b)
	{
		cout << (b ? "True" : "Flase") << endl;
	}
}




int main()
{
	{
		auto Hello1 = []()
		{
			printf("Hello1 \n");
		};

		auto Hello2 = [](char *data)
		{
			printf("%s \n", data);
		};

		auto Hello3 = [](char *data)
		{
			auto Hello4 = [](char *data)
			{
				printf("%s \n", data);
			};
			Hello4(data);
		};

		char buffer_C[1024] = "Hello aaaa";
		auto Hello5 = [/*这里会默认有一个const*/buffer_C](char *data)
		{
			printf("%s \n", data);
			printf("%s \n", buffer_C);
		};

		int testi = 10;
		//[&]作用域内的所有变量都能使用
		auto Hello6 = [&](char *data)
		{
			printf("%s \n", data);
			printf("%s \n", buffer_C);
			printf("%d \n", testi);
		};


		Hello1();
		char str[1024] = "Hello2";
		Hello2(str);
		char str1[1024] = "Hello3_4";
		Hello3(str1);
		char str2[1024] = "Hello5";
		Hello5(str2);
		char str3[1024] = "Hello6";
		Hello6(str3);
	}

	{
		TestA ta;
		ta.Init();
	}
}

