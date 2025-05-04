#include<stdio.h>
#include<string.h>
#include<stdlib.h>
unsigned char check[] = {21,33,15,25,37,91,25,57,95,58,59,48,116,7,67,63,9,90,52,12,116,63,30,45,39,33,18,22,31,0};
unsigned char key[100] = {"yunzh1jun"};
//moectf{D3bug_t0_g3t_7he_Key!}

__attribute((constructor)) static void fun()
{
    strcat(key,"TCL,trackYYDS");
}

int main()
{
    int len = strlen(key);
    unsigned char input[100];

    puts("I changed the key secretly, you can't find the right key!");
    puts("And I use random numbers to rot my input, you can never guess them!");
    puts("Unless you debug to get the key and random numbers...");
    puts("Now give me your flag:");

    scanf("%s", input);
    int len_ipt = strlen(input);

    for(int i = 0; i < len_ipt; i++)
        input[i] ^= key[i % len];

    for(int i = 0; i < len_ipt; i++)
        input[i] += rand() % 10;

    if(!strcmp(input, check))
        puts("\nRight! TTTTTQQQQQLLLLL!!!");
    else
        puts("QwQ, plz try again.");

    return 0;
}