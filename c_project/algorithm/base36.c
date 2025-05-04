#include <string.h>
#include <malloc.h>
#include "stdio.h"

unsigned char base36Table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void base36(const char *txt, char* output) {
    char *input = malloc(256);
    unsigned int len;
    int cur;
    unsigned char ch;
    unsigned char k36;
    unsigned char n2, n1, n0;
    unsigned char k36n1;
    unsigned char out_3digits[256] ={};

    strcpy(input, txt);
    memset(out_3digits, 0, sizeof(out_3digits));

    len = strlen(input);
    if (len >= 1) {
        cur = 2;
        do {
            ch = *input++;
            --len;
            k36 = 4 * ((ch / 36) & 0xFFFFFFC7 | (8 * ((ch / 36) & 7)));// 除以36的商 (456位 置0 | (留123位 << 3) << 2, 低3位<<5
            // 36: 100100, 100000 | 100, 100000: <<5, 100: << 2, 即拆分成 32 和 4 分别运算再 | 运算
            //  4 * ((ch / 36) & 0xFFFFFFC7) 为 123位 36倍数 a
            // 4 * (8 * ((ch / 36) & 7)) 为 456位 36倍数 b, a | b 即36倍数
            // k36 = 36k, 最接近 ch 的 36整数倍
            n2 = ch - k36;  // 减掉36k
            n1 = k36 / 36;  // XIX , 除1次得到十位数的值
            k36n1 = 4 * ((n1 / 36) & 0xC0000007 | (8 * ((n1 / 36) & 0x7FFFFFF))); // 以n1为基数 base36

            n2 = base36Table[n2];
            n1 = base36Table[n1 - k36n1]; // k36n1 是最高位 36的
            n0 = base36Table[(k36n1 / 36) % 36]; // 除2次得到百位数的值
            out_3digits[cur - 2] = n0; // IXX 最高位 out[0]
            out_3digits[cur - 1] = n1; // XIX 第二位 out[1]
            out_3digits[cur] = n2;     // XXI 第三位 out[2]
            cur += 3;
        } while (len);
    }
    printf("%s", out_3digits);
    // strcpy(output, out_3digits);
}

// 单字符 转为3字符 base36
int main(int argc, char *argv[], char **env) {
    setbuf(stdout, 0);
    char *txt = "12345678caaadaaaeaaa";
    char *output;
    base36(txt, output);
    printf("%s", output);
    return 0;
}