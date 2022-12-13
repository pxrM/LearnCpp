/*
	STL（容器、算法、迭代器）
	容器
	·deque
	·list
	·vector
	·map
*/

#include <iostream>
#include <vector>

using namespace std;


int main()
{
	vector<int> array1; //动态容器
	array1.push_back(99);	//算法 从尾巴处添加
	array1.push_back(10);
	cout << array1.size() << endl;

	cout << "-------------" << endl;

	vector<int>::iterator iter = array1.begin();
	while (iter != array1.end())
	{
		cout << *iter << endl;
		iter++;
	}
	cout << "-------------" << endl;
	for (vector<int>::iterator iter = array1.begin(); iter != array1.end(); iter++)
	{
		cout << *iter << endl;
	}

	vector<int> array2(10);	//预分配10个对象
	vector<int> array3(10, 0);	//预分配10个对象，每个元素等于0
	vector<int> array4(array2);	//用对象容器初始化
	vector<int> array5(array2.begin(), array2.begin() + 5);	//用迭代器初始化
	int testi[10] = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> array6(testi, testi + 5); //使用数组初始化

	vector<int> array7, array8;
	array7.assign(array2.begin(), array2.begin() + 4); //array2.begin()-array2.begin() + 4的元素赋值给array7
	array8.assign(7, 4);//预分配7个对象，每个元素等于4
	array8.push_back(22);
	auto &temptest1 = array8.front(); //取到第一个值
	auto &temptest2 = array8.back(); //取到最后一个值
	int &temptest3 = array8[1];
	array8.clear();
	if (array8.empty())
	{
		cout << "空的" << endl;
	}
	array8.assign(7, 4);
	array8.pop_back(); //删除最后一个
	array8.erase(array8.begin(), array8.begin() + 1); //删除这段的元素
	array8.insert(array8.begin() + 1, 9); //插入元素
	int size1 = array8.size(); //真实占用大小
	int size2 = array8.capacity(); //预分配的内存大小
	array8.resize(100);	//填充100
	array8.resize(100, 12);	//填充100 每个值为12
	array8.reserve(60);
	array8.swap(array7); //容器交换


	return 0;
}