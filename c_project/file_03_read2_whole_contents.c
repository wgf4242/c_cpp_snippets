#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char **env) {
    char *buffer = 0;
    long length;
    const char *filename = "C:\\test.txt";
    FILE *f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        // ftell 用于得到文件位置指针当前位置相对于文件首的偏移字节数。
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer) {
        // start to process your data / extract strings here...
        printf("%s", buffer);
        FILE *fptr = fopen("C:\\pg.txt", "wb");
        // buffer[length] = '\0';
        fprintf(fptr, "%s", buffer);
        // fprintf(fptr, "%s", "12345\n12345"); // first 5 character
        fclose(fptr);
        // fprintf(fptr, "%s", &(buffer[strlen(buffer) - 5])); // last 5 character
        // fprintf(fptr, "%.5s", buffer); // first 5 character
    }
}