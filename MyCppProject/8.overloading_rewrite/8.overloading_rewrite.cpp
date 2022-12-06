/*
	������	��c���Բ�֧������(��̬)��
	�������ڼ̳��е�����	������������еĺ�����������ʸ��� ��testb.FuncC()��
	���麯�����麯�����ڱ�����ǰ����뵽�麯�����У�
	��final���÷������󱳾���������Щ�麯����ϣ������ȥ��д���������Ѿ�����virtual�ؼ��֣�
	��override	����Ҫ�𵽼�����ã����鸸������������ǲ��ǿ��Ա���д��
*/

#include <iostream>

using namespace std;

/////////////////////// �������� ///////////////////////
void Func(int a)
{

}

void Func(int a, int b)
{

}

void Func(string str)
{

}
/////////////////////// �������� ///////////////////////

/////////////////////// ������&�麯�� ////////////////////////
class TestA
{
public:
	//��Ա������������
	void FuncC()
	{
		printf("TEST_A \n");
	}

	void FuncC(int a)
	{

	}

	void FuncC(int a, int b)
	{

	}

	void FuncC(string str)
	{

	}

public:
	//��̬����
	static void FuncS(int a)
	{

	}

	static void FuncS(int a, int b)
	{

	}

	static void FuncS(string str)
	{

	}

public:
	//�麯�����ڱ�����ǰ����뵽�麯�����У�virtual�ؼ���Ҳ�Ǹ�ָ���ռ�ĸ��ֽڣ�
	virtual void FuncV()
	{
		printf("A_FuncV \n");
	}

};


class TestB :public TestA
{
public:
	void FuncC()
	{
		printf("TEST_B \n");
	}

	virtual void FuncV() override
	{
		printf("B_FuncV \n");
	}
};



class IInterface
{
public:
	//���麯�����麯������=0�Ķ��Ǵ��麯�����������Ҫ��д��
	virtual void Init() = 0;
	virtual void Destroy() = 0;
};

class NewObject_Err : public IInterface
{

};

class NewObject : public IInterface
{
public:
	virtual void Init() final; //��ǰ����ֹ�ڴ��࣬�����಻����д��
	virtual void Destroy();
};
void NewObject::Init()
{
}

void NewObject::Destroy()
{
}

class NewObject_Two : public NewObject
{
public:
	//virtual void Init(){}  //error C3248: ��NewObject::Init��: ����Ϊ��final���ĺ����޷�����NewObject_Two::Init����д
	virtual void Destroy() {

	}
};

//�������ʾ���಻���ٱ��̳���
class NewObject_Three final :public IInterface
{

};

//class NewObject_Four :public NewObject_Three	// error C3246: ��NewObject_Four��: �޷��ӡ�NewObject_Three���̳У���Ϊ���ѱ�����Ϊ��final��
//{
//
//};


/////////////////////// ������&�麯�� ///////////////////////

/////////////////////////////////////////////////////////////////////
class HelloA
{

};

class HelloB :public HelloA
{

};


class HelloC :public HelloA
{
public:
	int a;
};

class HelloD
{
public:
	void Init(){}
};

class HelloE
{
public:
	virtual void Init() {}
};

class HelloF
{
public:
	virtual void Init1() {}
	virtual void Init2() {}
	virtual void Init3() {}
};

/////////////////////////////////////////////////////////////////////



int main()
{
	Func(1);
	Func(1, 2);
	Func("ssss");

	TestA::FuncS(2);
	TestA::FuncS(2, 6);
	TestA::FuncS("999");

	TestA test;
	test.FuncC(1);
	test.FuncC(1, 8);
	test.FuncC("1111");

	printf("//////////////\n");

	TestB testb;
	testb.FuncC(); //�ߵ����࣬�����߸���
	printf("//////////////\n");
	testb.FuncV(); //�ߵ�������д
	TestA *ta = &testb; //��ͨ�������������תΪ����Ļ�����ôִ�е��Ǹ�����ģ������virtual�Ļ�ִ�е����������
	ta->FuncV(); //�ߵ�������д
	ta->FuncC(); //�ߵĸ���


	//NewObject_Err objE; //error C2259: ��NewObject_Err��: �޷�ʵ����������
	NewObject obj;



	printf("//////////////\n");
	HelloA ah; // ���û�г�Ա�Ļ���Ĭ�Ϸ���һ���ֽڣ���ռλ�����ã��ñ�����֪���������Ҫȥ�ڴ����ģ������������Ա�������ͻ�����ռλ�Ƴ���
	int len = sizeof(ah);
	cout << "ah��С = " << len << "�ֽ�" << endl; //1

	HelloA ab;
	len = sizeof(ab);
	cout << "ab��С = " << len << "�ֽ�" << endl; //1

	HelloC ac;
	len = sizeof(ac);
	cout << "ac��С = " << len << "�ֽ�" << endl; //4

	HelloD ad;
	len = sizeof(ad);
	cout << "ad��С = " << len << "�ֽ�" << endl; //1

	//////////////////////////////���������virtual��������ĸ��ֽڣ����ĸ��ֽھ���virtualָ�룬ר��ָ���麯����
	HelloE ae;
	len = sizeof(ae);
	cout << "ae��С = " << len << "�ֽ�" << endl; //4

	HelloF af;
	len = sizeof(af);
	cout << "af��С = " << len << "�ֽ�" << endl; //4
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	return 0;
}


