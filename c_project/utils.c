#include <stdio.h>

static const int Rcon[10] =
        {
                0x01000000, 0x02000000,
                0x04000000, 0x08000000,
                0x10000000, 0x20000000,
                0x40000000, 0x80000000,
                0x1b000000, 0x36000000
        };

int GetIntFromChar(char c);
int GetWordFromStr(char * str);
int MergeArrayToInt(int array[4]);
void SplitIntToArray(int num, int array[4]);
void LeftLoop4Int(int array[4], int step);
int T(int num, int round);

void DFS(unsigned char * flag, int deep);

unsigned char flags[30][24];				//已经控制数据在30个以内 你们多设点也可以
unsigned int enc[24] = { 0x25, 0x15, 0xDF, 0xA2, 0xC0, 0x93, 0xAD, 0x14, 0x46, 0xC5, 0xF, 0x2E, 0x9A, 0xEB, 0x30, 0xF8, 0x20, 0xE9, 0xCB, 0x88, 0xC6, 0xBE, 0x8D, 0xE3 };
int x;

int main(void)
{
    int i, j, c;
    unsigned int t[66];

    unsigned char flag[24];
    flag[23] = 0xE3;
    DFS(flag, 23); //找到所有可能性放到flags

    unsigned int * pi = (unsigned int *)flags; //已无符号整形来访问 宽度为24 于4字节访问一次 所以为6
    //	for ( i = 0; i < 30 * 6; i++ )
    //	{
    //		printf("0x%X, ", pi[i]);
    //		if ( (i + 1) % 6 == 0 )
    //			printf("\n");
    //	}

    for ( c = 30; c <= 30 * 6; c += 6 )
    {
        for ( i = 60; i < 66; i++ )	//填好数据
            t[i] = pi[c + i - 60];
        for ( i = 59, j = 9; i >= 0; i-- )	//利用等式逆回去
        {
            if ( i % 6 == 0 )
            {
                t[i] = t[i + 6] ^ T(t[i + 5], j);
                j--;
            }
            else
                t[i] = t[i + 6] ^ t[i + 5];
            //			printf("t[%d] = 0x%X, ",i, t[i]);
        }
        unsigned char * p = (unsigned char *)t;
        for (i = 0; i < 24; i += 4) {
            printf("%c%c%c%c", p[i + 3], p[i + 2], p[i + 1], p[i]);//注意小端序
            fflush(stdout);
        }
        printf("\n");
    }

    return 0;
}

void DFS(unsigned char * flag, int deep)
{
    int i;
    if ( deep == 0 )
    {
        for ( i = 0; i < 24; i++ )
        {
            flags[x][i] = flag[i];
            //			printf("0x%X, ", flag[i]);
        }
        x++;
        //		puts("\n");
    }
    else
    {
        for ( i = 0; i < 0xFF; i++ )
        {
            if ( ((i ^ 0x41) ^ (i % 0x12 + flag[deep] + 0x05)) == enc[deep - 1] )
            {
                flag[deep - 1] = i;
                //				printf("0x%X, ", flag[deep - 1]);
                DFS(flag, deep - 1);
            }
        }
    }

}

int GetIntFromChar(char c)
{
    int result = (int) c;

    return result & 0x000000FF;
}

int GetWordFromStr(char * str)
{
    int one = GetIntFromChar(str[0]);
    one = one << 24;

    int two = GetIntFromChar(str[1]);
    two = two << 16;

    int three = GetIntFromChar(str[2]);
    three = three << 8;

    int four = GetIntFromChar(str[3]);

    return one | two | three | four;
}

int MergeArrayToInt(int array[4])
{
    int one = array[0] << 24;
    int two = array[1] << 16;
    int three = array[2] << 8;
    int four = array[3];

    return one | two | three | four;
}

void SplitIntToArray(int num, int array[4])
{
    int one = num >> 24;
    array[0] = one & 0x000000FF;

    int two = num >> 16;
    array[1] = two & 0x000000FF;

    int three = num >> 8;
    array[2] = three & 0x000000FF;

    array[3] = num & 0x000000FF;
}

void LeftLoop4Int(int array[4], int step)
{
    int tmp[4];
    int i;

    for ( i = 0; i < 4; i++ )
        tmp[i] = array[i];

    int index = step;
    for ( i = 0; i < 4; i++ )
    {
        array[i] = tmp[index];
        index++;
        index = index % 4;
    }
}

int T(int num, int round)
{
    int NumArray[4];

    SplitIntToArray(num, NumArray);

    LeftLoop4Int(NumArray, 1);

    int result = MergeArrayToInt(NumArray);

    return result ^ Rcon[round];
}