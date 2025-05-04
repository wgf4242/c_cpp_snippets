#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fileapi.h>

char *lpPath = "D:\\diskpar.bat";

void file_size1();

void winapiGetFileSize();

int main() {
    file_size1();
    winapiGetFileSize();

    return 0;

}

void winapiGetFileSize() {
    HANDLE pFile;
    pFile = CreateFile(lpPath, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING,        //打开已存在的文件
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    DWORD fileSize;
    fileSize = GetFileSize(pFile, NULL);          //得到文件的大小

    printf("filesize2: %ld\n", fileSize);
}

void file_size1() {
    FILE *fp = fopen(lpPath, "rb");

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);// needed for next read from beginning of file
    fclose(fp);

    printf("fileSize1: %ld\n", fileSize);
}
