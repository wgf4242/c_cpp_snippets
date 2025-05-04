#include <stdio.h>

int main() {
    FILE *file;
    char ch;
    int sum = 0;

    // 打开文件
    file = fopen("test.txt", "r");

    // 检查文件是否成功打开
    if (file == NULL) {
        printf("无法打开文件。\n");
        return 1;
    }

    // 读取文件字符并计算总和
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            int digit = ch - '0';
            sum += digit;
        }
    }

    // 关闭文件
    fclose(file);

    // 输出总和
    printf("总和为：%d\n", sum);

    return 0;
}