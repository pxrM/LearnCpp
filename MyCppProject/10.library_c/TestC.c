#include "TestC.h"
#include "stdio.h"


int __stdcall init_c(int a, int b)
{
    printf("init_c  %d  %d\n", a, b);
    return 0;
}

int __stdcall get_c_name(int a, int b)
{
    printf("get_c_name  %d  %d\n", a, b);
    return 0;
}

int get_c_private(int a, int b)
{
    printf("get_c_private  %d  %d\n", a, b);
    return 0;
}
