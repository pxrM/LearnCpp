#include "stdio.h"

void Hello(int a, int b) {

}

struct FStructC
{
	void (*Fun)(int, int);
	int a;
	int b;
}MyC;

void main1()
{
	MyC.Fun = Hello; //给函数指针赋值
}