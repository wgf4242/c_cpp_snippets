// gcc Read\&Write.c -o pwn -g
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void init()
{
    setvbuf(stderr,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stdin,0,2,0);
}

void menu()
{
	puts("Hello, my beeeest friend!Also a small chal for you!Good luck!");
    puts("1. Read num");
    puts("2. Write num");
    puts("0. Exit");
}

int main()
{
    init();
    menu();
    int nums[0x100];
    unsigned int choice,idx,num_to_write;
    memset(nums,0,sizeof(nums));
    while(1)
    {
        printf("> ");
        if (scanf("%u",&choice) < 0) goto Byebye;
        switch (choice)
        {
        case 1:
            printf("Idx:");
            if (scanf("%u",&idx) < 0) goto Byebye;
            printf("The num: %u\n",nums[idx]);
            break;
        case 2:
            printf("Idx:");
            if (scanf("%u",&idx) < 0) goto Byebye;
            printf("Num:");
            if (scanf("%u",&num_to_write) < 0) goto Byebye;
            nums[idx] = num_to_write;
            printf("Done!\n");
            break;
        default:
            goto Byebye;
            break;
        }
    }
    Byebye:
    printf("Byebye!\n");
}