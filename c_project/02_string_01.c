#include <string.h>
#include "stdio.h"
#include <assert.h>


void printCharArray(const char *s1);


void printCharArray2();

int getInt(const char *sa, const char *str2);

void cmp_work1();

int cmp_work2(const char *str1, const char *str2);

void test_strchr();

int main(int argc, char *argv[], char **env) {
    char s1[] = {'1', '2', '3', '\0'};
    printCharArray(s1);
    printCharArray2();

    cmp_work1();

    // char *str1 = "123";
    // char str1[] = "123";
    char str1[] = {"123"};
    printf("%d\n", cmp_work2(str1, "123"));

    test_strchr();
    return 0;
}

void test_strchr() {
    char string[17];
    char *ptr;
    strcpy(string, "Thisisastring");
    ptr = strchr(string, 'r');
    //str所指向的字符串中搜索第一次出现字符c（一个无符号字符）的位置。
    //返回指针 或 NULL(失败时)
    assert(strcmp(ptr, "ring") == 0);
}

int getInt1(char *inst1, char *inst2) {
    return strcmp(inst1, inst2);
}

void cmp_work1() {
    char inst1[] = "A";
    char inst2[] = "A";
    assert(strcmp(inst1, inst2) == 0);
}

void printCharArray(const char *s1) {
    printf("%s\n", s1);
}

void printCharArray2() {
    char s[3] = {0x31, 0x32, 0x33};
    s[3] = '\0';
    printf("%s\n", s);
}

int cmp_work2(const char *str1, const char *str2) {
    return strcmp(str1, str2);
    // strncmp("f11\0", "f", 1); // true
    // return memcmp(str1, str2);
}
