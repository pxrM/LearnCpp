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

	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;
	siPtr3 = nullptr;	//�������ü���	����������� ���Ǽ���Ϊ0��
	cout << "��ǰ���ü���=" << siPtr1.use_count() << endl;

	std::shared_ptr<int> siPtr4 = siPtr1;



	// ��ָ�� std::weak_ptr
	

	return 0;
}