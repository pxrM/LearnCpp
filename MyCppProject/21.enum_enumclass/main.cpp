#include <iostream> 
#include <vector>

// ö��ֵй¶�����������
enum TestA{
	A,
	B,
};
// �������A�ض���
enum TestB
{
	//A,
	C,
};


// ʹ��enum class���Ա���ö��ֵй¶�����������
enum class CA {
	A,
	B,
};
enum class CB
{
	A,
	C,
};


int main() {

	int a = A;	//ֱ��ʹ��
	CA ca = CA::A; //����ʹ���������޶���
	return 0;
}