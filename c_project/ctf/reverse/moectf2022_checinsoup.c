#include<stdio.h>
#include<string.h>

unsigned char check[] = { 0xcd,0x4d,0x8c,0x7d,0xad,0x1e,0xbe,0x4a,0x8a,0x7d,0xbc,0x7c,0xfc,0x2e,0x2a,0x79,0x9d,0x6a,0x1a,0xcc,0x3d,0x4a,0xf8,0x3c,0x79,0x69,0x39,0xd9,0xdd,0x9d,0xa9,0x69,0x4c,0x8c,0xdd,0x59,0xe9,0xd7,0 };

//moectf{p4tch_pr0gr4m_t0_d3c0mpi1e_it!}
void enc1(unsigned char* input)
{
    __asm {
            jz label
            jnz label
            _emit 0xe9
            label:
    }
    for (int i = 0; i < strlen((const char*)input) - 1; i++)
        input[i] += input[i + 1];
}

void enc2(unsigned char* input)
{
    __asm {
            jz label
            jnz label
            _emit 0xe9
            label:
    }

    for (int i = 0; i < strlen((const char*)input); i++)
        input[i] = ((input[i] >> 4) | (input[i] << 4)) & 0xff;
}

int my_strcmp(unsigned char* s1, unsigned char* s2)
{
    int i = 0, f = 0;

    while (i < 38)
        if (s1[i] == s2[i++])
            f++;

    if (f == 38)
        return 1;
    else
        return 0;
}

int main()
{
    unsigned char input[100];
    puts("I poisoned the program... Can you reverse it?!");
    puts("Come on! Give me your flag:");
    scanf_s("%s", input, 100);

    if (strlen((const char*)input) != 38)
    {
        puts("\nQwQ, please try again.");
        return 0;
    }

    enc1(input);
    enc2(input);

    if(my_strcmp(input,check))
        puts("\nTTTTTTTTTTQQQQQQQQQQQQQLLLLLLLLL!!!!");
    else
        puts("\nQwQ, please try again.");

    return 0;
}