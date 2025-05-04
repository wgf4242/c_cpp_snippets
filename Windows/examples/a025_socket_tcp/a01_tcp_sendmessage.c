/*
	�޴���
������->����ѡ��
          ->��ڵ�->����mainCRTStartup
          ->��ϵͳ->����Windows
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
        fprintf(stderr, "�޷����ļ�: %s\n", filePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(fileSize + 1);
    if (!content) {
        fprintf(stderr, "�ڴ����ʧ��\n");
        fclose(file);
        return;
    }

    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';

    int result = send(sock, content, fileSize, 0);
    if (result == SOCKET_ERROR) {
        fprintf(stderr, "����ʧ�ܣ��������: %d\n", WSAGetLastError());
    } else {
        printf("���ͳɹ�: %s\n", content);
    }

    free(content);
    fclose(file);
}

int main(int argc, char* argv[]) {
    const char* ip;
    int port;
    const char* filePath = "file.txt"; // Ĭ���ļ���

    if (argc < 3 || argc > 5) {
        fprintf(stderr, "ʹ�÷���: %s <ip> <port> [-f <filename>]\n", argv[0]);
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

    // ��ʼ��Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartupʧ�ܣ��������: %d\n", WSAGetLastError());
        return 1;
    }

    // �����׽���
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "�����׽���ʧ�ܣ��������: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // ���÷�������ַ
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // ���ӷ�����
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        fprintf(stderr, "����ʧ�ܣ��������: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // ÿ5�뷢��һ���ļ�����
    while (1) {
        sendFileContent(sock, filePath);
        Sleep(5000); // 5��
    }

    // �ر��׽���
    closesocket(sock);
    WSACleanup();
    return 0;
}