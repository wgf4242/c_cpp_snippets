#include <stdio.h>

// myPrintf 函数 hook 标记
void (*__myPrintf_hook)(char* string) = NULL;

void myPrintf(char* string)
{
    // 判断 hook 标记不为 NULL 则跳转执行 hook 函数
    void (*hook)(char*) = __myPrintf_hook;
    if (hook != NULL){
        return hook(string);
    }
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
    // 正常调用
    myPrintf("test");
    
    // 使用 hook
    __myPrintf_hook = myPrintfPlus;
    myPrintf("test");
    
    return 0;
}