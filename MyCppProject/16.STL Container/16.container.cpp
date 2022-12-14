/*
	STL���������㷨����������
	����
	��deque
	��list
	��vector
	��map

	string

	map

	˫������
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

	cout << "-------------" << endl << endl;






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

	return 0;
}