/*
	STL���������㷨����������



	������

		string

		map

		˫������

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
	vector<int> array1; //��̬����
	array1.push_back(99);	//�㷨 ��β�ʹ����
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

	vector<int> array2(10);	//Ԥ����10������
	vector<int> array3(10, 0);	//Ԥ����10������ÿ��Ԫ�ص���0
	vector<int> array4(array2);	//�ö���������ʼ��
	vector<int> array5(array2.begin(), array2.begin() + 5);	//�õ�������ʼ��
	int testi[10] = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> array6(testi, testi + 5); //ʹ�������ʼ��

	vector<int> array7, array8;
	array7.assign(array2.begin(), array2.begin() + 4); //array2.begin()-array2.begin() + 4��Ԫ�ظ�ֵ��array7
	array8.assign(7, 4);//Ԥ����7������ÿ��Ԫ�ص���4
	array8.push_back(22);
	auto &temptest1 = array8.front(); //ȡ����һ��ֵ
	auto &temptest2 = array8.back(); //ȡ�����һ��ֵ
	int &temptest3 = array8[1];
	array8.clear();
	if (array8.empty())
	{
		cout << "�յ�" << endl;
	}
	array8.assign(7, 4);
	array8.pop_back(); //ɾ�����һ��
	array8.erase(array8.begin(), array8.begin() + 1); //ɾ����ε�Ԫ��
	array8.insert(array8.begin() + 1, 9); //����Ԫ��
	int size1 = array8.size(); //��ʵռ�ô�С
	int size2 = array8.capacity(); //Ԥ������ڴ��С
	array8.resize(100);	//���100
	array8.resize(100, 12);	//���100 ÿ��ֵΪ12
	array8.reserve(60);
	array8.swap(array7); //��������


	int array9[] = { 6,88,5656,332,11,0 };
	vector<int> array10(array9, array9 + 6);
	//���� ������
	reverse(array10.begin(), array10.end());
	PrintVector(array10);
	//��С����
	sort(array10.begin(), array10.end());
	PrintVector(array10);
	//����
	vector<int> array11;
	array11.resize(array10.size());
	copy(array10.begin(), array10.end(), array11.begin());
	PrintVector(array11);
	//����
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
	cout << "��ȡ�����ַ������� size = " << str3.size() << endl;
	cout << "��ȡ��С length = " << str3.length() << endl;
	cout << "���ߴ� max_size = " << str3.max_size() << endl;
	cout << "Ԥ�����С capacity = " << str3.capacity() << endl;
	bool isEpty = str3.empty();	// �Ƿ�Ϊ��
	str3.c_str();	//�����ַ���ԭʼ����  C���
	str3.data(); //��ȡ�ڴ��ַ  C���
	str3.reserve(100);	 //Ԥ������ٿռ�
	string str4 = "----";
	str3.swap(str4);	//����
	char ch[] = "111111111";
	str3.insert(2, ch);	//����
	str3.append(str4); //�ϲ�
	char ch2 = 'p';
	str3.push_back(ch2);	//����ַ�
	str3.erase(5);	//ɾ���ַ���������������,5�����ȫ���������
	str3.clear();   //ɾ��ȫ���ַ�
	str3.assign("�����Ǹ�ֵ����");
	char ch3[] = "�����Ǹ�ֵ����";
	char ch4[] = "�滻";
	char ch5[] = "ssss5555ffffff22";
	string str5 = str3.replace(0, strlen(ch3), ch4);  //�滻
	str3.copy(ch5, strlen(ch5) - 3);	//����
	int cpos1 = str3.find('5');	//��ǰ������
	int cpos2 = str3.rfind('f');	//�Ӻ���ǰ��
	char ch6[] = "ff";
	int cpos3 = str3.find_first_of(ch6);	//��һ�γ���ff�ĵط�
	int cpos4 = str3.find_last_of(ch6);	//���һ�γ���ff�ĵط�
	int cpos5 = str3.find_first_not_of(ch6);	//���ص�һ�β�����ff�ĵط�
	int cpos6 = str3.find_last_not_of(ch6);		//�������һ�β�����ff�ĵط�
	string str6 = str3.substr(2, 5); //����2��5֮����ַ�
	str3.compare(ch6);	//�Ƚ��Ƿ���ͬ







	cout << "-------key����map-------" << endl;
	// key����	�����
	// �ռ�ռ���ʱȽϸ� ÿһ���ڵ㶼��һ���������Ӽ�
	map<int, string> map1;
	map<int, string> map2{ {1, "qqqqq"},{5, "fagsgdfg"} };
	map1[3] = "nihao";
	string element1 = map1.at(3);
	map1.insert(pair<int, string>(1, "����"));
	map1.insert(map<int, string>::value_type(2, "����"));
	map1.insert(make_pair(3, "����"));
	map1.insert({ { 9, "qqqqq" }, { 15, "fagsgdfg" } });
	cout << "���� = " << map1.size() << endl;
	auto pair1 = map1.equal_range(9); //��ȡһ��pair
	map1.erase(3);	//ɾ��keyΪ3��pair
	auto iter1 = map1.find(9);	//�������
	if (!map1.count(7))
	{
		map1.insert(make_pair(7, "û�а���7����ʼ����"));
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




	cout << "-------key����map-------" << endl;
	// key����	��ϣ
	// ������ϣ���ʱ��ܺ�ʱ
	unordered_map<int, int> unorderedMap1;
	unorderedMap1.insert(make_pair(1, 2));
	unorderedMap1.insert(make_pair(21, 22));
	unorderedMap1.insert(make_pair(10, 558));
	unorderedMap1.insert(make_pair(2, 586));
	unorderedMap1.insert(make_pair(6, 6));
	int elementUM1 = unorderedMap1.at(10);
	elementUM1 = unorderedMap1[1];
	int umCount = unorderedMap1.count(6);  //���key�����˼���
	auto umHash1 = unorderedMap1.hash_function();
	int hashtest = 22222;
	umHash1._Do_hash(hashtest);
	auto hashBucket = unorderedMap1.bucket(10);	//��ù�ϣͰλ��
	auto bucketCount = unorderedMap1.bucket_count();	//��ȡͰ������
	unorderedMap1.rehash(hashBucket);	//���¼����ϣ��
	auto buckerAverage = unorderedMap1.load_factor();	//����ÿ��Ͱƽ����Ԫ������





	cout << "-------key����multimap-------" << endl;
	// ��������ͬ��key
	multimap<int, string> multimap1;
	multimap1.insert(make_pair(10, "hello world"));
	multimap1.insert(make_pair(10, "hello"));
	multimap1.insert(make_pair(10, "world"));
	multimap1.insert(make_pair(9, "999"));
	auto multimapV1 = multimap1.find(10);	//��ƥ���һ��
	cout << multimapV1->second << endl;





	cout << "-------key����unordered_multimap-------" << endl;
	unordered_multimap<int, int> umm1;
	umm1.insert(make_pair(10, 6));
	umm1.insert(make_pair(10, 5));
	//�ж�����key�Ƿ����
	auto keyeq = umm1.key_eq();
	bool iseq = keyeq(10, 10);
	if (umm1.key_eq()(1,10))
	{
	}






	cout << "-------list------" << endl << endl;
	//��ʼ��
	list<string> nodelist1;
	list<string> nodelist2({ "aaa", "fdgdfgd", "fsdfsdg", "��ʼ��" });
	list<string> nodelist3 = { "aaa", "fdgdfgd", "fsdfsdg", "��ʼ��" };
	list<string> modelist4 = nodelist2;	//���
	list<string> modelist5(nodelist2); //���
	string nodestr1[] = { "gdfgf", "gggg", "666666666" };
	list<string> nodelist6(nodestr1, nodestr1 + 3);
	list<int>nodelist7 = { 1,22,645,121,12,0,12,4545,6666, 7856, 0 };
	//���
	nodelist6.push_back("������");
	nodelist6.push_front("��ǰ���");
	nodelist6.emplace_back("�����ӣ���push_back��ִ��һ�ο������죬Ч�ʺ�һ��");
	nodelist6.emplace_front("ǰ");
	//��ֵ
	nodelist6.assign({ "assign��ֵ","�������֮ǰ��Ԫ��","adsgdfgfd" });
	nodelist6.assign({}); //��Ϊ��
	nodelist6.assign(nodelist2.begin(), nodelist2.end());
	nodelist6.assign(10, "10��ֵ");
	//���������Ƴ���
	nodelist6.pop_back(); //�������һ��
	nodelist6.pop_front(); //������һ��
	//�Ƴ�	nodelist6.erase();
	nodelist3.remove("aaa");
	nodelist7.remove_if([](int i) {return i > 6666; }); //����6666��ȫ���Ƴ�
	 //�Ƴ��ظ���
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
	//��С
	nodelist6.size();
	//ȫ�����
	nodelist6.clear();
	//����
	nodelist6.swap(nodelist3);
	//����
	nodelist6.insert(nodelist6.begin(), "���뿪ʼλ��");
	nodelist6.insert(nodelist6.begin(), { "����", "��ʼ","λ��" });
	nodelist6.insert(nodelist6.end(), nodelist3.begin(), nodelist3.end());
	//����
	nodelist7.sort();	//Ĭ������
	nodelist7.sort(greater<int>()); //����

	//����
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
		cout << "cbegin��cend����const�������������޸�    " << *iter << endl;
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
		cout << "˳������� ��ǰ����    " << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = rbegin(testi1); iter != rend(testi1); iter++)
	{
		cout << "��������� �Ӻ���ǰ    " << *iter << endl;
	}
	cout << "-------------" << endl;
	for (auto iter = nodelist6.begin(); iter != nodelist6.end(); iter++)
	{
		cout << *iter << endl;
		advance(iter, 0);	//����
	}





	//��������
	cout << "-------forward_list-------" << endl;
	forward_list<int> forlist1;
	forlist1.assign(6, 10);
	for (auto &temp : forlist1)
	{
		cout << temp << endl;
	}
	forlist1.remove(10);
	forlist1.remove_if([](int a) {return a > 1; });
	//���
	forlist1.push_front(100);
	forlist1.emplace_after(forlist1.begin(), 1000);	//�ڴ���ĵ���������һ��λ�����
	forlist1.emplace_front(1);	//��ǰ��һ��λ�����
	
	for (forward_list<int>::const_iterator citer = forlist1.cbegin(); citer != forlist1.cend(); citer++) {
		cout << *citer << endl;
	}
	while (!forlist1.empty())
	{
		int value1 = forlist1.front();	//��ȡ��ǰ���ֵ
		cout << value1 << endl;
		forlist1.pop_front();	//������ǰ��ֵ
	}
	//forlist1.erase_after(forlist1.begin()); //ɾ��
	//forward_list<int> forlist2({ 45,4878,698,96,3699,99999,666 });
	//forlist1.splice_after(forlist1.begin(), forlist2); //��forlist2�������ƶ���forlist1��beginλ��
	//forlist1.splice_after(forlist1.before_begin(), forlist2); //��forlist2�������ƶ���forlist1��beginqǰ���λ��





	cout << "-------queue------" << endl;
	//����
	queue<int> q1;
	queue<int> q2({ 1,2,1245,2124,112,0,666666 });
	queue<int> q3(q2);
	q1.push(0);
	q1.push(21);
	q1.push(20);
	q1.push(252);
	q1.push(7);
	q1.push(8789);
	//����ͷ��Ԫ�� ��ɾ��
	int v1 = q1.front();
	//����β��Ԫ�� ��ɾ��
	int v2 = q1.back();
	//����
	cout << "��ǰ��С��" << q1.size() << endl;
	while (!q1.empty())
	{
		int v3 = q1.front();
		cout << v3 << endl;
		q1.pop();	//����ͷ�� ��ɾ��
	}
	cout << "��ǰ��С��" << q1.size() << endl;
	//����
	q1.swap(q2);
	cout << "��ǰ��С��" << q1.size() << endl;
	std::swap(q1, q2);





	//���ȼ����У����Զ�����
	cout << "-------priority_queue------" << endl;
	priority_queue<int> priority1;
	priority_queue<int> priority2;
	//���
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
	//���
	st1.push(56);
	//��С
	int stLen = st1.size();
	//����
	st1.swap(st2);
	while (!st1.empty())
	{
		int stv1 = st1.top();	//��ȡͷ��
		cout << stv1 << endl;
		st1.pop();	//����ͷ�� ��ɾ��
	}




	cout << "-------set-------" << endl;
	//�������ƽ�������
	// 1.����ʽ����		2.�ڲ�Ԫ�ػ��Զ�����	3.Ԫ��Ψһ
	set<int> set1({ 454878,454,656,666,333,1 });
	set<int> set2(set1);
	set<int> set3(set1.begin(), set1.end());
	set1.insert(100);
	set1.emplace(9); //���
	set1.emplace_hint(set1.end(), 99);	//���
	if (!set1.count(222222))	//�Ƿ����
	{
		set1.emplace(222222);
	}
	set1.erase(1);	//ɾ��
	set1.find(666);
	set1.clear();
	cout << set1.max_size() << endl;
	set1.swap(set2);
	auto setPair1 = set1.equal_range(99); //����99������һ�¸�Ԫ�صĵ�����
	auto setPair2 = set1.lower_bound(99); //����Ԫ��99�ĵ�����
	auto setPair3 = set1.upper_bound(99);	//����Ԫ��99��һ��Ԫ�صĵ�����
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




	cout << "-------����unordered_set-------" << endl;
	//�ڲ���ϣ
	unordered_set<int> us1;
	us1.insert(1213);
	us1.insert(99);
	us1.insert(86869);
	for (auto &temp : us1)
	{
		cout << temp << endl;
	}





	cout << "-------multiset-------" << endl;
	//��������ͬ��Ԫ��
	multiset<int> multiset1;
	multiset1.insert(1000);
	multiset1.insert(1000);
	multiset1.insert(1000);
	for (auto &temp : multiset1)
	{
		cout << temp << endl;
	}





	cout << "-------hash�������-------" << endl;
	hash<int> hash1;
	int encryptIndex = 123123;
	//���ܺ�Ĺ�ϣֵ
	auto encrypt1 = hash1._Do_hash(encryptIndex);
	auto encrypt2 = hash1(encryptIndex);
	cout << encrypt1 << endl;
	cout << encrypt2 << endl;





	cout << "-------array-------" << endl;
	array<int, 4> farray1({ 1,6,8,89 }); //��������Ϊ4��array
	farray1.fill(100); //�޸�����Ԫ�ص�ֵΪ100
	auto farrayhead = farray1.data();	//��ȡ�׵�ַ
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