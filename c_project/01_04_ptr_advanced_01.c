// https://mp.weixin.qq.com/s/6RO0S68tSHs-WlddZg-PSQ

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

// 如何用函数指针调用函数
void ptr_run_func() {
    int Func(int x);   /*声明一个函数*/
    int (*p)(int x);  /*定义一个函数指针*/
    p = Func;          /*将Func函数的首地址赋给指针变量p*/
    p = &Func;         /*将Func函数的首地址赋给指针变量p*/
}

int Max(int x, int y)  //定义Max函数
{
    int z;
    if (x > y) {
        z = x;
    } else {
        z = y;
    }
    return z;
}

void ptr_run_func2() {
    int (*p)(int, int);  //定义一个函数指针
    int a, b, c;
    p = Max;  //把函数Max赋给指针变量p, 使p指向Max函数
    /*
     p = Max可以改成 p = &Max
     c = (*p)(a, b) 可以改成 c = p(a, b)
    */
    printf("please enter a and b:");
    scanf("%d%d", &a, &b);
    c = (*p)(a, b);  //通过函数指针调用Max函数
    printf("a = %d\nb = %d\nmax = %d\n", a, b, c);
}

typedef void(*FunType)(int);

//前加一个typedef关键字，这样就定义一个名为FunType函数指针类型，而不是一个FunType变量。
//形式同 typedef int* PINT;
void callFun(FunType fp, int x) {
    fp(x);//通过fp的指针执行传递进来的函数，注意fp所指的函数有一个参数
}

void myFun(int x) {
    printf("myFun: %d\n", x);
}

void hisFun(int x) {
    printf("hisFun: %d\n", x);
}

void herFun(int x) {
    printf("herFun: %d\n", x);
}

void (* func5(int, int, float ))(int, int)
{
}
int main(void) {
    // 1. 如何用函数指针调用函数
    // ptr_run_func();
    // ptr_run_func2();

    // 3. 函数指针作为某个函数的参数
    callFun(myFun, 100);//传入函数指针常量，作为回调函数
    callFun(hisFun, 200);
    callFun(herFun, 300);

    // 4. 函数指针作为函数返回类型
    // func5

    // 5. 函数指针数组
    /* 方法1 */
    void (*func_array_1[5])(int, int, float);

    /* 方法2 */
    typedef void (*p_func_array)(int, int, float);
    p_func_array func_array_2[5];

    return 0;
}
