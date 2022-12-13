/*
	·基本的输入输出
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
	// 空格后会被截掉，如果输入是连续的可以用它 aaaaaaaaa aa >> aaaaaaaaa
	//cin >> buffer;	
	// 可以输出带空格的
	//cin.getline(buffer, 1024);
	//cout << buffer << endl;	//
	//cerr << "cerr" << endl; //不带缓存
	//clog << "clog" << endl; //带缓存


	//fstream 读写流
	//ofstream //创建文件流并输入信息
	//ifstream //输出文件流
	//fstream //创建文件、写入信息、读取信息
	ofstream writefile;
	writefile.open("如果不存在文件会自动创建.txt", ios::app); // ios::app 以追加的方式写入，而不是覆盖
	cout << "开始写入信息" << endl;
	cin.getline(buffer, 1024);
	writefile << buffer << endl;
	writefile.close();

	ifstream readfile;
	readfile.open("如果不存在文件会自动创建.txt");
	cout << "开始读取信息 只读取一行" << endl;
	readfile >> buffer;
	cout << buffer << endl;
	//readfile.close();

	cout << "开始读取信息 读取全部" << endl;
	char buffer2[1024] = { 0 };
	readfile.seekg(0, ios::end); //将游标移动到最后一个位置
	int filelen = readfile.tellg(); //获取游标位置
	readfile.seekg(0, ios::beg); //再将游标移动到开头
	readfile.read(buffer2, filelen); //读取数据
	cout << buffer2 << endl;
	readfile.close();

	/*
		ios::app   追加写入
		ios::ate   打开文件时游标自动定位到文件末尾
		ios::in    读取
		ios::out   写入
		ios::trunc 截断，如果文件存在打开时进行截断，文件长度设置为0
	*/
	fstream file;
	file.open("如果不存在文件会自动创建.txt", ios::out | ios::in);
	file << "xxxxxxxxxx" << endl;
	file.close();
	char buffer3[1024] = { 0 };
	FileRead("如果不存在文件会自动创建.txt", buffer3);

	FileCopy("14.io.cpp", "拷贝C屁屁.cpp");


;
	return 0;
}