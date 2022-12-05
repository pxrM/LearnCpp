/*
	���ز�����

	˫Ŀ�����	+(��)��-(��)��*(��)��/(��)��%(ȡģ)
	��ϵ�����	==(���ڵ���)��!=(������)��<(С��)��>(����)��<=(С�ڵ���)��>=(���ڵ���)
	�߼������	||(�߼���)��&&(�߼���)��!(�߼���)
	��Ŀ�����	+(��)��-(��)��*(ָ��)��&(ȡ��ַ)
	++(����)��--(�Լ�)
	λ�����	|(��λ��)��&(��λ��)��~(��λȡ��)��^(��λ���)��<<(����)��>>(����)
	��ֵ�����	=��+=��-=��*=��/=��%=��&=��|=��^=��<<=��>>=
	�ռ��������ͷ�	new��delete��new[]��delete[]
	���������	()�������á�->��Ա���ʡ�,���š�[]�±�

	���������ص��������
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

	//���庯����
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
		char* mp; //����ʱҪע�⣬��Ҫ���·����ڴ�

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
	AssetHello::mprintcount << "hello" << " cƨƨ" << AssetHello::mendcount;
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