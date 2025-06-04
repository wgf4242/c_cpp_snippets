#include <stdio.h>

// 使用 __attribute__((constructor)) 标记的函数会在函数库加载时就运行，且会先于程序
__attribute__((constructor)) 
static void setup(void) {
    fprintf(stderr, "hook libc is setup.\n");
}

// 使用 __attribute__((destructor)) 标记的函数会在程序退出时运行
__attribute__((destructor))
static void cleanup(void) {
    fprintf(stderr, "hook libc is cleanup.\n");
}

// 示例函数
void example_function(void) {
    printf("This is an example function.\n");
}

int main(void) {
    printf("Main function started.\n");
    example_function();
    printf("Main function ended.\n");
    return 0;
}