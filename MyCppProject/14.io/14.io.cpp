/*
	���������������
*/

#include <iostream>
#include <fstream>


using namespace std;



void FileRead(const char *inflilename, char *inbuffer)
{
	ifstream readFile;
	readFile.open(inflilename);
	readFile.seekg(0, ios::end);
	int filelen = readFile.tellg();
	readFile.seekg(0, ios::beg);
	readFile.read(inbuffer, filelen);
	cout << inbuffer << endl;
	readFile.close();
}

bool FileCopy(const char *inCopyFileName, const char *inTargetFileName)
{
	char buffer[4096] = { 0 };
	ifstream ReadFile;
	ofstream WriteFile;
	ReadFile.open(inCopyFileName);
	WriteFile.open(inTargetFileName);

	//while (ReadFile >> buffer)
	//{
	//	cout << buffer << endl;
	//	WriteFile << buffer << endl;
	//}
	ReadFile.seekg(0, ios::end);
	int filelen = ReadFile.tellg();
	ReadFile.seekg(0, ios::beg);
	ReadFile.read(buffer, filelen);
	WriteFile << buffer;

	ReadFile.close();
	WriteFile.close();

	return true;
}

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
	ofstream writefile;
	writefile.open("����������ļ����Զ�����.txt", ios::app); // ios::app ��׷�ӵķ�ʽд�룬�����Ǹ���
	cout << "��ʼд����Ϣ" << endl;
	cin.getline(buffer, 1024);
	writefile << buffer << endl;
	writefile.close();

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

	/*
		ios::app   ׷��д��
		ios::ate   ���ļ�ʱ�α��Զ���λ���ļ�ĩβ
		ios::in    ��ȡ
		ios::out   д��
		ios::trunc �ضϣ�����ļ����ڴ�ʱ���нضϣ��ļ���������Ϊ0
	*/
	fstream file;
	file.open("����������ļ����Զ�����.txt", ios::out | ios::in);
	file << "xxxxxxxxxx" << endl;
	file.close();
	char buffer3[1024] = { 0 };
	FileRead("����������ļ����Զ�����.txt", buffer3);

	FileCopy("14.io.cpp", "����Cƨƨ.cpp");


;
	return 0;
}