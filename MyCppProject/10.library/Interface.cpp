#include "Interface.h"
#include <iostream>


class Hello :public IInterface
{
public:
	Hello();

	virtual void Init();
	virtual void Destroy();
	virtual char* GetName();

private:
	char Name[1024];
};

Hello::Hello()
{
	memset(Name, 0, 1024);
	strcpy(Name, "HelloHello");
}

void Hello::Init()
{
	printf("Hello::Init()\n");
}

void Hello::Destroy()
{
	printf("Hello::Destroy()\n");
}

char *Hello::GetName()
{
	return Name;
}



IInterface *IInterface::CreateInterface()
{
	return new Hello();
}

