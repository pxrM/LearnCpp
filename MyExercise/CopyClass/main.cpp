/*
	ǳ���������
*/

#include "QObj.h"
#include "SObj.h"
#include "LRUCache.h"

/// <summary>
/// ǳ��������
/// </summary>
/// <param name="obj"></param>
void ShallowCopy(QObj& obj)
{
	// ������������Ĭ�ϵĿ������캯����������Ĭ�ϵĿ������캯����һ��ǳ������
	// �����´����Ķ���obj2û���Լ��Ķ����ռ䣬obj2.pָ�����obj1.p��ָ����ڴ��ַ��
	QObj obj2 = obj;
	obj2.Show();
}

int main()
{
	/*
	* ����Ĵ��������ͨ�����ģ� ԭ�����ڣ���������ʱ��ͬһ���ڴ��ַ0x0001������obj1��obj2һ�����������Ρ�
	* ������ִ����test(obj1)ʱ������obj2��������ָ��obj2.p��ָ����ڴ��ַ0x0001���ͷţ�
	* ���Ե�����ִ�е�obj1.Show()ʱ��ʹ�����Ѿ����ͷŵ����ڴ�0x0001��ַ���Ӷ��������д���
	*/
	//QObj obj1(const_cast<char*>("123"));
	//ShallowCopy(obj1);
	//obj1.Show();

	SObj obj3((char*)"asd");
	SObj obj4((char*)"fgh");
	// ERR  ��ʱ����obj3=obj1;�����ɵ���Ĭ�ϵĿ������캯������Ϊ��������Ѿ���һ���Ѿ�����ı��������Բ�������ÿ������캯����
	//obj4 = obj3; 
	/*
		��������ҪŪ���obj3=obj1��Obj obj3 = obj1֮�������:
			obj4 = obj3; �ǽ�obj3��ֵ��obj4��=��ֵ�뿽������û��ʲô������
					=�ڸ�ֵʱ��c++�������Լ�����Ĭ�ϵĿ������죨ǳ�����������������޶�������޹أ�
			SObj obj5 = obj4; ������ʹ��obj4������obj5����ʱ������ж�����������캯�����ͻ�ʹ�������
		Ҫ���������⣬��Ҫ��ʾ����=������ˡ�
	*/
	SObj obj5 = obj4;

	LRUCache<int, int, 2> LruCache;
	LruCache.put(1, 10);
	LruCache.put(2, 20);
	LruCache.put(3, 30);
	std::cout << "��: " << LruCache.get(1) << std::endl;

	system("pause");

	return 0;
}