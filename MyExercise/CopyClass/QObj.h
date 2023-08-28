/**
* 
* C++�ڽ���ǳ����ʱ��ֻ����ջ�����ڴ�ռ��ַ���������������ڴ�ռ����ݣ�
* ��ǳ����ֻ������ָ��ĳ�Ա������ָ�뱾����������ָ����ָ��Ķ��������ݡ�
* 
*/

#include <iostream>

using namespace std;

//����1.1
class QObj
{
public:
	QObj(char* tp)
	{
		len = strlen(tp);
		p = (char*)malloc(len + 1); //�����ڴ�ռ䣬��СΪ len + 1 �ֽڣ�������ֹ�� \0 �Ŀռ䣩������������ڴ��ַ���浽ָ����� p �С�
		strcpy_s(p, len + 1, tp); //���ַ��� tp ������֮ǰ������ڴ�ռ� p �У�ȷ�����ᷢ���ڴ����
	}
	~QObj()
	{
		if (p)
		{
			free(p);
			p = nullptr;
			len = 0;
		}
	}
	void Show()
	{
		cout << *p << *(p + 1) << *(p + 2) << endl;
	}
private:
	char* p;
	int len;
};
