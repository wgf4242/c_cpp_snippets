// 看 17_CalcArrayCube 二维数组利用指针求和
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "stdio.h"
void char_test();

void ptrPlus1(char *ptr_s1);

void charPtrInit();

void charPtrInit2() {
    char a[] = "123456";
    char* input = a;
    strcpy(input, "888888"); // 不能超长度
    assert(strcmp(input, "888888") == 0);

}
void ptrConvert(){
    char a[] = {0x12, 0x34, 0x56, 0x78};
    int *two_bytes = &a[2];
    printf("address is %x\n", two_bytes);
    printf("value is %x\n", *two_bytes);
    strcpy(two_bytes, "1234444");
    printf("value is %s", *two_bytes);
    // TODO: 输出了多余的字符. 要修复一下.
}

int main(void) {
    charPtrInit();
    charPtrInit2();
    char_test();
    ptrConvert();
    return 0;
}

void charPtrInit() {
    char *input = malloc(20);
    strcpy(input, "aaaabaaacaaadaaaeaaa");
}


void char_test() {
    char *ptr_s1 = "12345";
    assert(ptr_s1[0] == '1');
    ptrPlus1(ptr_s1);  // 里面操作不影响外面
    assert(ptr_s1[0] == '1');
}

void ptrPlus1(char *ptr_s1) {
    ptr_s1++;
    assert(ptr_s1[0] == '2');
}
