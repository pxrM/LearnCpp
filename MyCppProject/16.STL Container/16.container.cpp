/*
	STL（容器、算法、迭代器）
	容器
	·deque
	·list
	·vector
	·map

	string

	map

	双向链表
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;


template<class T>
struct MNode
{
	MNode() :Next(nullptr), Previous(nullptr)
	{

	}

	MNode *Next;
	MNode *Previous;
	T Data;
};


void PrintVector(vector<int> &temp)
{
	cout << "-------------" << endl;
	for (vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
	{
		cout << *iter << endl;
	}
}

int main()
{
	MNode<string> mnode;
	mnode.Data = "mn1";
	mnode.Previous = nullptr;

	mnode.Next = new MNode<string>();
	mnode.Next->Data = "mn2";
	mnode.Next->Previous = &mnode;

	mnode.Next->Next = new MNode<string>();
	mnode.Next->Next->Data = "mn3";
	mnode.Next->Next->Previous = mnode.Next;

	mnode.Next->Next->Next = new MNode<string>();
	mnode.Next->Next->Next->Data = "mn4";
	mnode.Next->Next->Next->Previous = mnode.Next->Next;

	auto PrintNode = [&]()
	{
		cout << "-------------" << endl;
		MNode<string> *mnodeptr = &mnode;
		while (mnodeptr)
		{
			cout << mnodeptr->Data << endl;
			mnodeptr = mnodeptr->Next;
		}
	};

	PrintNode();

	auto RemoveNode = [&](const string &removestring)
	{
		MNode<string> *ptr = &mnode;
		while (ptr)
		{
			if (ptr->Data == removestring)
			{
				ptr->Previous->Next = ptr->Next;
				if (ptr->Next)
				{
					ptr->Next->Previous = ptr->Previous;
				}
				delete ptr;
				ptr = nullptr;
			}
			else
			{
				ptr = ptr->Next;
			}
		}
	};
	RemoveNode("mn4");
	PrintNode();




	cout << "-------------" << endl;




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


	int array9[] = { 6,88,5656,332,11,0 };
	vector<int> array10(array9, array9 + 6);
	//倒置 不排序
	reverse(array10.begin(), array10.end());
	PrintVector(array10);
	//从小到大
	sort(array10.begin(), array10.end());
	PrintVector(array10);
	//复制
	vector<int> array11;
	array11.resize(array10.size());
	copy(array10.begin(), array10.end(), array11.begin());
	PrintVector(array11);
	//查找
	auto elementtemp = find(array11.begin(), array11.end(), 88);

	cout << "-------------" << endl << endl;





	/*
		string
	*/
	string str1 = "hello string";
	string str2 = "222222222222";
	string str3 = str1 + str2;
	cout << str3 << endl;
	for (string::iterator iter = str3.begin(); iter != str3.end(); iter++)
	{
		cout << *iter << endl;
	}
	cout << "获取容器字符串数量 size = " << str3.size() << endl;
	cout << "获取大小 length = " << str3.length() << endl;
	cout << "最大尺寸 max_size = " << str3.max_size() << endl;
	cout << "预分配大小 capacity = " << str3.capacity() << endl;
	bool isEpty = str3.empty();	// 是否为空
	str3.c_str();	//返回字符串原始数据  C风格
	str3.data(); //获取内存地址  C风格
	str3.reserve(100);	 //预分配多少空间
	string str4 = "----";
	str3.swap(str4);	//交换
	char ch[] = "111111111";
	str3.insert(2, ch);	//插入
	str3.append(str4); //合并
	char ch2 = 'p';
	str3.push_back(ch2);	//添加字符
	str3.erase(5);	//删除字符（可以设置区域,5后面的全部被清掉）
	str3.clear();   //删除全部字符
	str3.assign("这里是赋值操作");
	char ch3[] = "这里是赋值操作";
	char ch4[] = "替换";
	char ch5[] = "ssss5555ffffff22";
	string str5 = str3.replace(0, strlen(ch3), ch4);  //替换
	str3.copy(ch5, strlen(ch5) - 3);	//拷贝
	int cpos1 = str3.find('5');	//从前往后找
	int cpos2 = str3.rfind('f');	//从后往前找
	char ch6[] = "ff";
	int cpos3 = str3.find_first_of(ch6);	//第一次出现ff的地方
	int cpos4 = str3.find_last_of(ch6);	//最后一次出现ff的地方
	int cpos5 = str3.find_first_not_of(ch6);	//返回第一次不包含ff的地方
	int cpos6 = str3.find_last_not_of(ch6);		//返回最后一次不包含ff的地方
	string str6 = str3.substr(2, 5); //返回2到5之间的字符
	str3.compare(ch6);	//比较是否相同

	cout << "-------------" << endl << endl;






	map<int, string> map1;
	map<int, string> map2{ {1, "qqqqq"},{5, "fagsgdfg"} };

	map1[3] = "nihao";
	string element1 = map1.at(3);

	map1.insert(pair<int, string>(1, "插入"));
	map1.insert(map<int, string>::value_type(2, "插入"));
	map1.insert(make_pair(3, "插入"));
	map1.insert({ { 9, "qqqqq" }, { 15, "fagsgdfg" } });

	cout << "长度 = " << map1.size() << endl;

	auto pair1 = map1.equal_range(9); //获取一个pair

	map1.erase(3);	//删除key为3的pair

	auto iter1 = map1.find(9);	//二叉查找

	if (!map1.count(7))
	{
		map1.insert(make_pair(7, "没有包含7，开始插入"));
	}

	//for (const pair<int, string> &temp : map1)
	for (auto &temp : map1)
	{
		if (temp.first == 3)
		{
			cout << temp.second << endl;
		}
	}
	for (map<int, string>::iterator iter = map1.begin(); iter != map1.end(); iter++)
	{
		if (iter->first == 3)
		{
			cout << iter->second << endl;
			break;
		}
	}

	return 0;
}