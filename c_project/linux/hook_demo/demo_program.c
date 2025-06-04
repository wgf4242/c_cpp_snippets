#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== Hook Demo Program ===\n");
    
    // 测试内存分配
    printf("\n1. Testing memory allocation:\n");
    void *ptr1 = malloc(100);
    void *ptr2 = malloc(200);
    
    // 测试字符串比较
    printf("\n2. Testing string comparison:\n");
    if (strcmp("hello", "world") == 0) {
        printf("Strings are equal\n");
    } else {
        printf("Strings are different\n");
    }
    
    // 测试printf
    printf("\n3. Testing printf:\n");
    printf("This is a test message\n");
    
    // 释放内存
    printf("\n4. Testing memory deallocation:\n");
    free(ptr1);
    free(ptr2);
    
    printf("\n=== Demo completed ===\n");
    return 0;
}