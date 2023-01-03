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

	list
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <list>

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

	cout << "-------------" << endl << endl;




	//初始化
	list<string> nodelist1;
	list<string> nodelist2({ "aaa", "fdgdfgd", "fsdfsdg", "初始化" });
	list<string> nodelist3 = { "aaa", "fdgdfgd", "fsdfsdg", "初始化" };
	list<string> modelist4 = nodelist2;	//深拷贝
	list<string> modelist5(nodelist2); //深拷贝
	string nodestr1[] = { "gdfgf", "gggg", "666666666" };
	list<string> nodelist6(nodestr1, nodestr1 + 3);
	list<int>nodelist7 = { 1,22,645,121,12,0,12,4545,6666, 7856, 0 };
	//添加
	nodelist6.push_back("向后添加");
	nodelist6.push_front("向前添加");
	nodelist6.emplace_back("向后添加，比push_back少执行一次拷贝构造，效率好一点");
	nodelist6.emplace_front("前");
	//赋值
	nodelist6.assign({ "assign赋值","会清理掉之前的元素","adsgdfgfd" });
	nodelist6.assign({}); //置为空
	nodelist6.assign(nodelist2.begin(), nodelist2.end());
	nodelist6.assign(10, "10个值");
	//弹出（会移除）
	nodelist6.pop_back(); //弹出最后一个
	nodelist6.pop_front(); //弹出第一个
	//移除	nodelist6.erase();
	nodelist3.remove("aaa");
	nodelist7.remove_if([](int i) {return i > 6666; }); //大于6666的全部移除
	nodelist7.unique(); //移除重复的
	struct UniqueTest
	{
		UniqueTest()
		{
			a = 0;
		}
		UniqueTest(int i) :a(i)
		{
		}

		int a;

		bool operator==(const UniqueTest &v)
		{
			return a == v.a;
		}
	};
	list<UniqueTest> nodelist8;
	nodelist8.push_front(UniqueTest(77));
	nodelist8.push_front(UniqueTest(77));
	nodelist8.push_front(UniqueTest(525));
	nodelist8.push_front(UniqueTest(3636));
	nodelist8.unique();
	//大小
	nodelist6.size();
	//全部清除
	nodelist6.clear();
	//交换
	nodelist6.swap(nodelist3);
	//插入
	nodelist6.insert(nodelist6.begin(), "插入开始位置");
	nodelist6.insert(nodelist6.begin(), { "插入", "开始","位置" });
	nodelist6.insert(nodelist6.end(), nodelist3.begin(), nodelist3.end());
	//排序
	nodelist7.sort();	//默认升序
	nodelist7.sort(greater<int>()); //降序

	//遍历
	for (list<string>::iterator iter = nodelist6.begin(); iter != nodelist6.end(); iter++)
	{
		cout << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto &tmep : nodelist6)
	{
		cout << tmep << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = nodelist6.cbegin(); iter != nodelist6.cend(); iter++)
	{
		cout << "cbegin和cend代表const迭代器，不可修改    " << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = nodelist6.rbegin(); iter != nodelist6.rend(); iter++)
	{
		cout << *iter << endl;
	}
	cout << "-------------" << endl;
	int testi1[] = { 1,2,3,5,45,66,99 };
	for (auto iter = begin(testi1); iter != end(testi1); iter++)
	{
		cout << "顺序迭代器 从前往后    " << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = rbegin(testi1); iter != rend(testi1); iter++)
	{
		cout << "逆序迭代器 从后往前    " << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = nodelist6.begin(); iter != nodelist6.end(); iter++)
	{
		cout << *iter << endl;
		advance(iter, 0);	//步长
	}

	return 0;
}