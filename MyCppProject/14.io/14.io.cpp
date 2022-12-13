/*
	·基本的输入输出
*/

#include <iostream>
#include <fstream>


using namespace std;


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
	ofstream file;
	file.open("如果不存在文件会自动创建.txt", ios::app); // ios::app 以追加的方式写入，而不是覆盖
	cout << "开始写入信息" << endl;
	cin.getline(buffer, 1024);
	file << buffer << endl;
	file.close();

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
;
	return 0;
}