#include <iostream>

class Monster
{
public:
	Monster();
	~Monster();

	int a;
	int b;

	/* 
	���������ڱ���׶Σ���Ѹú����Ĵ��븴�Ƶ����øú����ĵط���
	��������ʹ�����ڳ�Ա�ͽṹ���Լ�ȫ�ֺ�����
	��Ҫע��ĵط���
		1.����������÷���.h�ļ��У������Ͷ��岻��ֿ�
		2.��������һ����Ҫ��̵Ĵ��룬��ò�Ҫ����ѭ�����ݹ顢Switch�Լ�һЩ���ӵ����㣬�����Ӱ��Ч��
	*/
	inline int GetP()const {
		return b;
	}

private:

};

Monster::Monster()
{

}

Monster::~Monster()
{
}

void main()
{
}