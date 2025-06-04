#include <stdio.h>

void myPrintf(char* string)
{
    printf("%s:\t", "NoHook");
    printf("%s\n", string);
}

void myPrintfPlus(char *string)
{
    printf("%s:\t", "Hook");
    printf("%s\n", string);
}

int main(int argc, char const *argv[])
{
    // 使用函数指针封装实现hook
    void (*myPrintfPtr)(char*) = myPrintfPlus;
    myPrintfPtr("test");
    
    return 0;
}