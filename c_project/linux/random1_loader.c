// gcc -o random1_loader random1_loader.c -L. -l:random1.so 
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/kali/vmware/test/del/newstartctf2022/_tmp

#include <stdio.h>

// 定义 random1.so 中的函数导出
extern void set_seed(unsigned long seed);
extern int random_number();

int main() {
    // 调用 set_seed 函数设置种子为 42
    set_seed(42);

    // 调用 random_number 函数生成随机数并打印
    int num = random_number();
    printf("随机数: %d\n", num);

    return 0;
}