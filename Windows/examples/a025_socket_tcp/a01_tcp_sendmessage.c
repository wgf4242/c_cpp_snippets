/*
	无窗口
链接器->所有选项
          ->入口点->输入mainCRTStartup
          ->子系统->窗口Windows
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

void sendFileContent(SOCKET sock, const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        fprintf(stderr, "无法打开文件: %s\n", filePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(fileSize + 1);
    if (!content) {
        fprintf(stderr, "内存分配失败\n");
        fclose(file);
        return;
    }

    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';

    int result = send(sock, content, fileSize, 0);
    if (result == SOCKET_ERROR) {
        fprintf(stderr, "发送失败，错误代码: %d\n", WSAGetLastError());
    } else {
        printf("发送成功: %s\n", content);
    }

    free(content);
    fclose(file);
}

int main(int argc, char* argv[]) {
    const char* ip;
    int port;
    const char* filePath = "file.txt"; // 默认文件名

    if (argc < 3 || argc > 5) {
        fprintf(stderr, "使用方法: %s <ip> <port> [-f <filename>]\n", argv[0]);
        return 1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    if (argc == 5 && strcmp(argv[3], "-f") == 0) {
        filePath = argv[4];
    }

    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in server;

    // 初始化Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup失败，错误代码: %d\n", WSAGetLastError());
        return 1;
    }

    // 创建套接字
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "创建套接字失败，错误代码: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // 连接服务器
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        fprintf(stderr, "连接失败，错误代码: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 每5秒发送一次文件内容
    while (1) {
        sendFileContent(sock, filePath);
        Sleep(5000); // 5秒
    }

    // 关闭套接字
    closesocket(sock);
    WSACleanup();
    return 0;
}