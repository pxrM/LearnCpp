#include <iostream>


using namespace std;

int main()
{
	// ��ָ��
	int *iPtr = new int;

	// ����ָ��	std::shared_ptr
	std::shared_ptr<int>  siPtr1(iPtr);
	std::shared_ptr<int> siPtr2 = std::make_shared<int>(12);	//����һ���ռ䣬����ֵ����Ϊ12
	std::shared_ptr<int> siPtr3(siPtr1);	//�������ü���	//���м��
	std::shared_ptr<int> siPtr4 = siPtr1;
	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;
	siPtr4 = nullptr;	//�������ü���	����������� ���Ǽ���Ϊ0��
	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;
	int *iPtr2 = siPtr1.get();	//תΪԭʼָ�루��ָ�룩
	int ivalue = *siPtr1;	//��ȡֵ
	bool bSingle = siPtr1.unique(); //�ǲ���Ψһ��
	//siPtr1.swap(siPtr2);	//����
	siPtr1.reset();	//reset = (siPtr1 = nullptr)

	// ��ָ�� std::weak_ptr
	

	return 0;
}