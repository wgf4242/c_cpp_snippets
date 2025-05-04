#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include <exception>

int key = 0x19;

unsigned char box[] = { 172, 4, 88, 176, 69, 150, 159, 46, 65, 21, 24, 41, 177, 51, 170, 18, 13, 137, 230, 250, 243, 196, 189, 231, 112, 138, 148, 193, 133, 157, 163, 242, 63, 130, 142, 215, 3, 147, 61, 19, 5, 107, 65, 3, 150, 118, 227, 177, 138, 74, 34, 85, 196, 25, 245, 85, 166, 31, 14, 97, 39, 203, 31, 158, 90, 122, 227, 21, 64, 148, 71, 222, 0, 1, 145, 102, 183, 205, 34, 100, 245, 165, 156, 104, 165, 82, 134, 189, 176, 221, 118, 40, 171, 22, 149, 197, 38, 44, 246, 57, 190, 0, 165, 173, 227, 147, 158, 227, 5, 160, 176, 29, 176, 22, 11, 91, 51, 149, 164, 9, 22, 135, 86, 31, 131, 78, 74, 60, 85, 54, 111, 187, 76, 75, 157, 177, 174, 229, 142, 200, 251, 14, 41, 138, 187, 252, 32, 98, 4, 45, 128, 97, 214, 193, 204, 59, 137, 197, 139, 213, 38, 88, 214, 182, 160, 80, 117, 171, 23, 131, 127, 55, 43, 160, 29, 44, 207, 199, 224, 229, 73, 201, 250, 107, 192, 152, 102, 153, 146, 0, 2, 212, 117, 70, 34, 5, 53, 209, 75, 197, 173, 224, 142, 69, 59, 80, 21, 181, 46, 133, 48, 137, 84, 18, 222, 241, 90, 240, 43, 167, 27, 74, 38, 93, 152, 212, 161, 190, 209, 77, 126, 56, 222, 11, 10, 84, 184, 115, 109, 173, 140, 30, 217, 49, 95, 86, 126, 189, 72, 50, 152, 46, 62, 235, 162, 29 };
unsigned char check[] = { 30,112,122,110,234,131,158,239,150,226,178,213,153,187,187,120,185,61,110,56,66,194,134,255,99,189,250,121,163,109,96,148,179,66,17,195,144,137,189,239,212,151,248,123,139,11,45,117,126,221,203,0 };

int FilterFunc(int dwExceptionCode)
{
    if (dwExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
        return EXCEPTION_EXECUTE_HANDLER;

    return EXCEPTION_CONTINUE_SEARCH;
}

int my_strcmp(unsigned char* s1, unsigned char* s2)
{
    int i = 0, f = 0;

    while (i < 51)
        if (s1[i] == s2[i++])
            f++;

    if (f == 51)
        return 1;
    else
        return 0;
}

int main()
{
    unsigned char input[100];
    //unsigned char input[100] = {"moectf{Re4d_4ssemb1y_t0_g3t_the_m4gic_key_0f_Tr4ck}"};
    int index = 0, tmp, i;

    puts("Can you read my assembly in exception?");
    puts("Give me your flag:");
    scanf_s("%s", input, 100);

    if (strlen((const char*)input) != 51)
    {
        puts("\nQwQ, please try again.");
        return 0;
    }

    for (i = 0; i < 51; i++)
    {

        __try {
            index = (0x7f * index + 0x66) % 0xff;
            tmp = index >> 7;
            tmp = 1 / tmp;
        }
        __except (FilterFunc(GetExceptionCode())) {
            key = (97 * key + 101) % 233;
            key ^= 0x29;
            //printf("catch i = %d\n", i);
        }

        input[i] ^= box[key];

    }

    if (strcmp(check, input))
        puts("\nTTTTTTTTTTQQQQQQQQQQQQQLLLLLLLLL!!!!");
    else
        puts("\nQwQ, please try again.");
    return 0;
}