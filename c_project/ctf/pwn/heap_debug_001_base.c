#include <stdio.h>
#include <stdlib.h>
int main(){
        void *ptr = malloc(0x10);
        void *ptr1= malloc(0x90);
        void *ptr2= malloc(0x800);
        return 0;
}

/*
gdb out
b main
vmmap 查看内存情况，
ni 执行到 malloc
malloc(0x10)，但却申请了0x21大小的空间
heap
*/