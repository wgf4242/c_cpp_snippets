#include <stdio.h>
#include <stdlib.h>

static void cat(FILE *fp) {
    char line[4096];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
}

int main(int argc, char **argv) {
    FILE *file = fopen("example.txt", "r"); // 打开文件，"example.txt"是你要读取的文件名
    cat(file);
    fclose(file);
    return (0);
}
