// http://saladk.com/index.php/archives/15/#toc-6isAsciiDigit
// https://secondbc.github.io/SecondBC/2021/12/10/Data-Lab/
#include <stdio.h>
#include <stdbool.h>

void print_bin(int number) {
    int bit = sizeof(int) * 8;
    int i;
    for (i = bit - 1; i >= 0; i--) {
        int bin = (number & (1 << i)) >> i;
        printf("%d", bin);
    }
    printf("\n");
}

int bitXor(int x, int y) {
    return ~((~x) & (~y)) & (~(x & y));
}

int tmin(void) { // 最小的二进制补码整数

    return 2 << 30;

}

// 所有奇数位都设置为1是包括了 0xAAAAAAAA 和 0xffffffff 两种情况，实验要求只能使用的数据是 0 - 0xff, 所以用 0xAA构造掩码 0xAAAAAAAA，用 x & 0xAAAAAAAA ，排除 0xffffffff的情况
int allOddBits(int x) {
    int mask = 0xAA + (0xAA << 8); // A -> 1010
    mask = mask + (mask << 16);
    x = (x & mask) ^ mask;
    return !x;
}

int negate(int x) {
    return (~x + 1);
}

int conditional(int x, int y, int z) {
    int flag = (~!!x) + 1;
    return ((flag & y) | (~flag & z));
}

/**
 * 需要写一个函数判断参数是不是在'0'-'9'范围之间。（也就是int类型的30-39）
   因为本题要返回1或者0，所以return中应该使用&（两个条件需要同时满足）。
   如果x≥30，则(x + (~min + 1))就≥0，则最高位就是0.反之，最高位就是1.
 * @param x
 * @return
 */
int isAsciiDigit(int x) {
    int min = 0x30;
    int max = 0x39;

    return (!((x + (~min + 1)) >> 31)) & (!((max + (~x + 1)) >> 31));
    //tip: return with &.
}

int isAsciiDigit2(int x) {
    int sign = 1 << 31;
    int upperBound = ~(sign | 0x39);   /*if > 0x39 is added, result goes negative*/
    int lowerBound = ~0x30;            /*when < 0x30 is added, result is negative*/

    /*now auto_add x and check the sign bit for each*/
    upperBound = sign & (upperBound + x) >> 31;
    lowerBound = sign & (lowerBound + 1 + x) >> 31;
    /*if either result is negative, it is not in desired range*/
    return !(upperBound | lowerBound);
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int sign_x = (x >> 31) & 1; // x高位
    int sign_y = (y >> 31) & 1; // y高位
    int signXsubY = ((~x + 1 + y) >> 31) & 1;
    /**
     * sign_x & ~sign_y,  先判断 x 和 y 的符号位 ， 如果x , y 的符号位不同 ， 则直接判断 ，假设成立 则 （sign_x & ~sign_y）应该为 1
     * !(sign_x ^ sign_y), 如果 x , y 的符号位是相同的 ， 则用 y - x 的符号位来继续判断大小 ， 用
     *                     !(sign_x ^ sign_y) 来判断 x , y 的符号位是否相同 ， 相同则进入 下一部判断 ， 在前面的题目 ， 我们已经知道 ~x + 1 即为 x 的负数，通过判断符号位来 描述大小关系
     */
    return (sign_x & ~sign_y) | (!(sign_x ^ sign_y) & !signXsubY);
}

/**
 * 仅使用 ~ & ^ | + << >> 实现 ！运算符
 * 利用 0 的相反数 还是 0 的性质 即 0+1 = 0 -0 + 1 = 0
 */
int logicalNeg(int x) {
    return (((~x + 1) >> 31) + 1) & ((x >> 31) + 1);
}

/** howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int b16,b8,b4,b2,b1,b0;
    int flag = x >> 31;
    x = (flag&~x)|(~flag&x); //x为非正数则不变 ,x 为负数 则相当于按位取反
    b16 = !!(x >> 16) << 4; //如果高16位不为0,则我们让b16=16
    x >>= b16; //如果高16位不为0 则我们右移动16位 来看高16位的情况
    //下面过程基本类似
    b8 = !!(x >> 8) << 3;
    x >>= b8;
    b4 = !!(x >> 4) << 2;
    x >>= b4;
    b2 = !!(x >> 2) << 1;
    x >>= b2;
    b1 = !!(x >> 1);
    x >>= b1;
    b0 = x;
    return b0+b1+b2+b4+b8+b16+1;
}


int main() {
    print_bin(8);
    printf("%d\n", bitXor(3, 8)); // 011 | 100 => 111 = 11
    printf("%d\n", tmin());
    printf("%d\n", allOddBits(0xAAAAAAAA));
    printf("%d\n", negate(11));
    printf("%d\n", conditional(2 < 1, 991992, 59193));
    printf("%d\n", conditional(2 > 1, 991992, 59193));
    printf("%d\n", isAsciiDigit('a'));
    printf("%d\n", isAsciiDigit('0'));
    printf("%d\n", isAsciiDigit('9'));

    return 0;
}
