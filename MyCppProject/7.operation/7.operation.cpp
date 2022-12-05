/*
	重载操作符

	双目运算符	+(加)、-(减)、*(乘)、/(除)、%(取模)
	关系运算符	==(等于等于)、!=(不等于)、<(小于)、>(大于)、<=(小于等于)、>=(大于等于)
	逻辑运算符	||(逻辑或)、&&(逻辑与)、!(逻辑非)
	单目运算符	+(正)、-(负)、*(指针)、&(取地址)
	++(自增)、--(自减)
	位运算符	|(按位或)、&(按位与)、~(按位取反)、^(按位异或)、<<(左移)、>>(右移)
	赋值运算符	=、+=、-=、*=、/=、%=、&=、|=、^=、<<=、>>=
	空间申请与释放	new、delete、new[]、delete[]
	其它运算符	()函数调用、->成员访问、,逗号、[]下标

	不可以重载的运算符：
		.
		*		
		->*
		::
		sizeof
		?:
		#
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

namespace AssetHello
{
	enum EHello
	{
		EA,
		EB,
	};

	struct SHello
	{
		void Init() {}
		void Str() {}
	};

	class IInterface
	{

	};

	class CHello :public IInterface
	{

	};

	//定义函数体
	void AssetHelloFunc() {}
	CHello* GetHello();


	class Mistream
	{
	public:
		Mistream()
		{
			memset(&mstr, 0, 1024);
			mi = 0;
		}

		~Mistream()
		{
			if (mp)
			{
				delete mp;
				mp = nullptr;
			}
		}

		void Print()
		{
			printf(mstr);
			if (mp)
			{
				printf(mp);
			}
		}

		Mistream& Print_R()
		{
			printf(mstr);
			return *this;
		}

		Mistream& operator =(Mistream& p)
		{
			mp = (char*)malloc(1024);
			strcpy(this->mp, p.mp);

			return *this;
		}

		Mistream& operator =(const char* p)
		{
			strcpy(mstr, p);
			return *this;
		}

		Mistream& operator <<(const char* p)
		{
			printf(p);
			return *this;
		}

		Mistream& operator <<(const int p)
		{
			printf("%d", p);
			return *this;
		}

		Mistream& operator <<(const Mistream& p)
		{
			printf("\n");
			return *this;
		}

		Mistream& operator ++(int)
		{
			mi++;
			return *this;
		}

		bool operator !=(const Mistream& p)
		{
			return this->mi != p.mi;
		}

	public:
		char* mp; //拷贝时要注意，需要重新分配内存

	private:
		char mstr[1024];
		int mi;
	};

	Mistream mprintcount;
	Mistream mendcount;

}

namespace AssetHello
{
	CHello* GetHello()
	{
		return nullptr;
	}
}


int main()
{
	AssetHello::mprintcount << "hello" << AssetHello::mendcount;
	AssetHello::mprintcount << "hello" << " c屁屁" << AssetHello::mendcount;
	AssetHello::mprintcount << 66 << AssetHello::mendcount;

	AssetHello::mprintcount = "123456";
	AssetHello::mprintcount.Print();
	(AssetHello::mprintcount = ".963.").Print();
	(AssetHello::mprintcount = "999").Print_R() << AssetHello::mendcount;

	AssetHello::Mistream A, B;
	A.mp = (char*)malloc(1024);
	strcpy(A.mp, "hello ==");
	B = A;
	B.Print();

	return 0;
}