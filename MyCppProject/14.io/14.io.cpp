/*
	���������������
*/

#include <iostream>
#include <fstream>


using namespace std;


int main()
{
	cout << "iostream" << endl;
	char buffer[1024] = { 0 };
	// �ո��ᱻ�ص�����������������Ŀ������� aaaaaaaaa aa >> aaaaaaaaa
	//cin >> buffer;	
	// ����������ո��
	//cin.getline(buffer, 1024);
	//cout << buffer << endl;	//
	//cerr << "cerr" << endl; //��������
	//clog << "clog" << endl; //������


	//fstream ��д��
	//ofstream //�����ļ�����������Ϣ
	//ifstream //����ļ���
	//fstream //�����ļ���д����Ϣ����ȡ��Ϣ
	ofstream file;
	file.open("����������ļ����Զ�����.txt", ios::app); // ios::app ��׷�ӵķ�ʽд�룬�����Ǹ���
	cout << "��ʼд����Ϣ" << endl;
	cin.getline(buffer, 1024);
	file << buffer << endl;
	file.close();

	ifstream readfile;
	readfile.open("����������ļ����Զ�����.txt");
	cout << "��ʼ��ȡ��Ϣ ֻ��ȡһ��" << endl;
	readfile >> buffer;
	cout << buffer << endl;
	//readfile.close();

	cout << "��ʼ��ȡ��Ϣ ��ȡȫ��" << endl;
	char buffer2[1024] = { 0 };
	readfile.seekg(0, ios::end); //���α��ƶ������һ��λ��
	int filelen = readfile.tellg(); //��ȡ�α�λ��
	readfile.seekg(0, ios::beg); //�ٽ��α��ƶ�����ͷ
	readfile.read(buffer2, filelen); //��ȡ����
	cout << buffer2 << endl;
	readfile.close();
;
	return 0;
}