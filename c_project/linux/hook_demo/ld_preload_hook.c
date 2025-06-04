//gcc -fPIC -shared -o libmyhook.so ld_preload_hook.c -ldl
#include <stdio.h>
#include <dlfcn.h>

/*hook的目标是strcmp，所以typedef了一个STRCMP函数指针
hook的目的是要控制函数行为，从原库libc.so.6中拿到strcmp指针，保存成old_strcmp以备调用*/

//定义 strcmp 函数原型指针类型
typedef int(*STRCMP)(const char*, const char*);

//重写 strcmp 函数内部逻辑
int strcmp(const char *s1, const char *s2)
{
    //从原运行库解析原型函数指针
    static void *handle = NULL;
    static STRCMP old_strcmp = NULL;
    
    if( !handle )
    {
        //当库被装入后，返回的句柄作为给 dlsym() 的第一个参数，以获得符号在库中的地址
        handle = dlopen("libc.so.6", RTLD_LAZY);
        old_strcmp = (STRCMP)dlsym(handle, "strcmp");
    }
    
    //自定义操作
    printf("oops!!! hack function invoked. s1=<%s> s2=<%s>\n", s1, s2);
    
    //运行原函数
    return old_strcmp(s1, s2);
}