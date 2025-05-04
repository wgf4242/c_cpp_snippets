#include <stdio.h>
#include <string.h>

void char1();

void char2_memset(const char *src);

void createPointer();

void functionPointer3Immediately();

void char2_passptr();

int Add(int x, int y) { return x + y; }

void test(char *str) {};
void test2(){ printf("test2 function\n");}

void functionPointer2() {
    int (*pf)(int, int) = &Add;//函数指针定义，返回值类型和参数类型与函数Add（）相同
    int i = pf(1, 2);

}

void functionPointer1() {
    void ( *pt)(char *) = &test;
}

void functionPointer4call(int n, void (*fn)()) {
    printf("%d, ", n);
    fn();
}

int main() {
    createPointer();
    char1();
    char2_passptr();
    char src[] = "Hello World!";
    // char src[] = "Hello World!"; // 1
    // char *src = "Hello World!";     // 2
    char2_memset(src);


    // https://blog.csdn.net/m0_46569169/article/details/124318184#t6
    functionPointer1();
    functionPointer2();
    functionPointer3Immediately();
    void ( *fn)() = &test2;
    functionPointer4call(4, fn);
    return (0);
}

void bf(char *c) {
    printf("%c", *c);
}

void char2_passptr() {
    char a = 'a';
    bf(&a);
}

void functionPointer3Immediately() {
    (*(void (*)())(&test2))();
    // cast = void (*)(); // 函数指针
    // addr = (cast)(&test2); // 置换地址
    // (*addr)();  // 调用地址
}


void createPointer() {
    int section[80];
    char section1[64] = "\0";
    int *student = section; // int *student = &section[0];
    char *string = "abcd";
    static char *weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // NULL
    char *a = 0;
    char *b = NULL;

    // >C++11
    // char *ch = nullptr;
}

void char1() {
    char src[40];
    strcpy(src, "Hello World!");
    printf("Result： %s\n", src);
}

void char2_memset(const char *src) {
    char dest[12];
    memset(dest, '\0', sizeof(dest));
    strcpy(dest, src);
    printf("memset： %s\n", dest);
}
