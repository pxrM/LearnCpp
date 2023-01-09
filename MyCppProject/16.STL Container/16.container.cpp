/*
	STL（容器、算法、迭代器）



	容器：

		string

		map

		双向链表

		list

		queue

		stack

		set

		forward_list

		priority_queue

		hash

		multiset

		multimap

		array

		unordered_map

		unordered_multimap

		unordered_set

		unordered_multiset
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <forward_list>
//#include <concurrent_priority_queue.h>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "MIterator.h"


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



struct PriorityQTest
{
	PriorityQTest(int i) :price(i) {
	}

	string name;
	int price;

	friend bool operator<(const PriorityQTest &a, const PriorityQTest &b)
	{
		return a.price < b.price;
	}
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








	cout << "------vector-------" << endl;
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






	cout << "-------string------" << endl;
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







	cout << "-------key有序map-------" << endl;
	// key有序	红黑树
	// 空间占有率比较高 每一个节点都有一个父级和子集
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




	cout << "-------key无序map-------" << endl;
	// key无序	哈希
	// 建立哈希表的时候很耗时
	unordered_map<int, int> unorderedMap1;
	unorderedMap1.insert(make_pair(1, 2));
	unorderedMap1.insert(make_pair(21, 22));
	unorderedMap1.insert(make_pair(10, 558));
	unorderedMap1.insert(make_pair(2, 586));
	unorderedMap1.insert(make_pair(6, 6));
	int elementUM1 = unorderedMap1.at(10);
	elementUM1 = unorderedMap1[1];
	int umCount = unorderedMap1.count(6);  //这个key出现了几次
	auto umHash1 = unorderedMap1.hash_function();
	int hashtest = 22222;
	umHash1._Do_hash(hashtest);
	auto hashBucket = unorderedMap1.bucket(10);	//获得哈希桶位置
	auto bucketCount = unorderedMap1.bucket_count();	//获取桶的数量
	unorderedMap1.rehash(hashBucket);	//重新计算哈希表
	auto buckerAverage = unorderedMap1.load_factor();	//返回每个桶平均的元素数量





	cout << "-------key有序multimap-------" << endl;
	// 可以有相同的key
	multimap<int, string> multimap1;
	multimap1.insert(make_pair(10, "hello world"));
	multimap1.insert(make_pair(10, "hello"));
	multimap1.insert(make_pair(10, "world"));
	multimap1.insert(make_pair(9, "999"));
	auto multimapV1 = multimap1.find(10);	//会匹配第一个
	cout << multimapV1->second << endl;





	cout << "-------key无序unordered_multimap-------" << endl;
	unordered_multimap<int, int> umm1;
	umm1.insert(make_pair(10, 6));
	umm1.insert(make_pair(10, 5));
	//判断两个key是否相等
	auto keyeq = umm1.key_eq();
	bool iseq = keyeq(10, 10);
	if (umm1.key_eq()(1,10))
	{
	}






	cout << "-------list------" << endl << endl;
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
	 //移除重复的
	nodelist7.unique();
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





	//单向链表
	cout << "-------forward_list-------" << endl;
	forward_list<int> forlist1;
	forlist1.assign(6, 10);
	for (auto &temp : forlist1)
	{
		cout << temp << endl;
	}
	forlist1.remove(10);
	forlist1.remove_if([](int a) {return a > 1; });
	//添加
	forlist1.push_front(100);
	forlist1.emplace_after(forlist1.begin(), 1000);	//在传入的迭代器后面一个位置添加
	forlist1.emplace_front(1);	//在前面一个位置添加
	
	for (forward_list<int>::const_iterator citer = forlist1.cbegin(); citer != forlist1.cend(); citer++) {
		cout << *citer << endl;
	}
	while (!forlist1.empty())
	{
		int value1 = forlist1.front();	//获取最前面的值
		cout << value1 << endl;
		forlist1.pop_front();	//弹出最前的值
	}
	//forlist1.erase_after(forlist1.begin()); //删除
	//forward_list<int> forlist2({ 45,4878,698,96,3699,99999,666 });
	//forlist1.splice_after(forlist1.begin(), forlist2); //把forlist2的数据移动到forlist1的begin位置
	//forlist1.splice_after(forlist1.before_begin(), forlist2); //把forlist2的数据移动到forlist1的beginq前面的位置





	cout << "-------queue------" << endl;
	//队列
	queue<int> q1;
	queue<int> q2({ 1,2,1245,2124,112,0,666666 });
	queue<int> q3(q2);
	q1.push(0);
	q1.push(21);
	q1.push(20);
	q1.push(252);
	q1.push(7);
	q1.push(8789);
	//访问头部元素 不删除
	int v1 = q1.front();
	//访问尾部元素 不删除
	int v2 = q1.back();
	//遍历
	cout << "当前大小：" << q1.size() << endl;
	while (!q1.empty())
	{
		int v3 = q1.front();
		cout << v3 << endl;
		q1.pop();	//弹出头部 会删除
	}
	cout << "当前大小：" << q1.size() << endl;
	//交换
	q1.swap(q2);
	cout << "当前大小：" << q1.size() << endl;
	std::swap(q1, q2);





	//优先级队列（会自动排序）
	cout << "-------priority_queue------" << endl;
	priority_queue<int> priority1;
	priority_queue<int> priority2;
	//添加
	priority1.emplace(666);
	priority1.push(11);
	priority1.push(56);
	priority1.push(68767);
	priority2.push(0);
	priority2.push(12);
	priority2.push(7789);
	//
	priority1.size();
	//priority1.swap(priority2);
	//
	while (!priority1.empty())
	{
		int pv1 = priority1.top();
		cout << pv1 << endl;
		priority1.pop();
	}
	cout << "--------------" << endl;
	priority_queue<PriorityQTest> priority3;
	priority3.push(PriorityQTest(56));
	priority3.push(PriorityQTest(1));
	priority3.push(PriorityQTest(22));
	priority3.push(PriorityQTest(857));
	priority3.push(PriorityQTest(576));
	while (!priority3.empty())
	{
		PriorityQTest pv2 = priority3.top();
		cout << pv2.price << endl;
		priority3.pop();
	}




	cout << "------stack-------" << endl;
	stack<int> st1({ 1,454,65,4545,1212 });
	stack<int> st2(st1);
	stack<int> st3 = st1;
	vector<int> ve1({ 145,545,312487,6878 });
	stack<int, vector<int>> st4(ve1);
	//添加
	st1.push(56);
	//大小
	int stLen = st1.size();
	//交换
	st1.swap(st2);
	while (!st1.empty())
	{
		int stv1 = st1.top();	//获取头部
		cout << stv1 << endl;
		st1.pop();	//弹出头部 会删除
	}




	cout << "-------set-------" << endl;
	//红黑树的平衡二叉树
	// 1.关联式容器		2.内部元素会自动排序	3.元素唯一
	set<int> set1({ 454878,454,656,666,333,1 });
	set<int> set2(set1);
	set<int> set3(set1.begin(), set1.end());
	set1.insert(100);
	set1.emplace(9); //添加
	set1.emplace_hint(set1.end(), 99);	//添加
	if (!set1.count(222222))	//是否包含
	{
		set1.emplace(222222);
	}
	set1.erase(1);	//删除
	set1.find(666);
	set1.clear();
	cout << set1.max_size() << endl;
	set1.swap(set2);
	auto setPair1 = set1.equal_range(99); //返回99和它的一下个元素的迭代器
	auto setPair2 = set1.lower_bound(99); //返回元素99的迭代器
	auto setPair3 = set1.upper_bound(99);	//返回元素99下一个元素的迭代器
	auto setv1 = set1.begin();
	auto setv2 = set1.end();
	auto setv3 = set1.cbegin();
	auto setv4 = set1.cend();
	auto setv5 = set1.rbegin();
	auto setv6 = set1.rend();
	auto setv7 = set1.crbegin();
	auto setv8 = set1.crend();
	bool bEmy = set1.empty();
	for (auto &temp : set1)
	{
		cout << temp << endl;
	}
	cout << "--------------" << endl;
	for (set<int>::iterator iter = set1.begin(); iter != set1.end(); iter++)
	{
		cout << *iter << endl;
	}




	cout << "-------无序unordered_set-------" << endl;
	//内部哈希
	unordered_set<int> us1;
	us1.insert(1213);
	us1.insert(99);
	us1.insert(86869);
	for (auto &temp : us1)
	{
		cout << temp << endl;
	}





	cout << "-------multiset-------" << endl;
	//可以有相同的元素
	multiset<int> multiset1;
	multiset1.insert(1000);
	multiset1.insert(1000);
	multiset1.insert(1000);
	for (auto &temp : multiset1)
	{
		cout << temp << endl;
	}





	cout << "-------hash运算加密-------" << endl;
	hash<int> hash1;
	int encryptIndex = 123123;
	//加密后的哈希值
	auto encrypt1 = hash1._Do_hash(encryptIndex);
	auto encrypt2 = hash1(encryptIndex);
	cout << encrypt1 << endl;
	cout << encrypt2 << endl;





	cout << "-------array-------" << endl;
	array<int, 4> farray1({ 1,6,8,89 }); //声明长度为4的array
	farray1.fill(100); //修改所有元素的值为100
	auto farrayhead = farray1.data();	//获取首地址
	auto farrayV1 = farray1[2];
	auto farrayV2 = farray1.at(0);
	auto farrayV3 = farray1.back();
	auto farrayV4 = farray1.front();




	cout << "-------TArray-------" << endl;
	//
	struct MIterTest
	{
		MIterTest(int InA) :ID(InA) {

		}

		bool operator!=(const MIterTest &A)
		{
			return A.ID != ID;
		}

		inline int GetID() { return ID; }


	protected:
		int ID = 0;
	};

	TArray<MIterTest> MArr1;
	MIterTest ME1(1);
	MArr1.Add(ME1);
	MArr1.Add(MIterTest(10));
	MArr1.Add(MIterTest(99));
	MArr1.Add(MIterTest(698));
	for (TArray<MIterTest>::MIteraotr iter = MArr1.Begin(); iter != MArr1.End(); iter++)
	{
		cout << (*iter).GetID() << endl;
	}
	MArr1.RemoveAt(1);
	for (int i = 0; i < MArr1.Num(); i++)
	{
		cout << MArr1[i]->GetID() << endl;
	}




	return 0;
}