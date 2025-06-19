#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <getopt.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#ifndef CONSOLE_MODE
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

#define BUFFER_SIZE 1024
#define DEFAULT_IP "10.63.81.34"
#define DEFAULT_PORT "9999"

// 在后台模式下禁用输出
#ifdef CONSOLE_MODE
#define LOG_PRINTF printf
#else
#define LOG_PRINTF(...) ((void)0)
#endif

void print_usage(const char* program_name) {
    LOG_PRINTF("�÷�: %s [ѡ��]\n", program_name);
    LOG_PRINTF("ѡ��:\n");
    LOG_PRINTF("  -i <IP>     ������ IP ��ַ (Ĭ��: %s)\n", DEFAULT_IP);
    LOG_PRINTF("  -p <�˿�>   �������˿� (Ĭ��: %s)\n", DEFAULT_PORT);
    LOG_PRINTF("  -h          ��ʾ�˰�����Ϣ\n");
    LOG_PRINTF("\nʾ��:\n");
    LOG_PRINTF("  %s -i 101.201.56.60 -p 8090\n", program_name);
}

SOCKET tcp_connect(const char* host, const char* port) {
    SOCKET sock;
    struct addrinfo hints, *result;
    int ret;
    
    while (1) {
        LOG_PRINTF("�������ӵ� %s:%s...\n", host, port);
        
        // ��ʼ��hints�ṹ
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        
        // ��ȡ��ַ��Ϣ
        ret = getaddrinfo(host, port, &hints, &result);
        if (ret != 0) {
            LOG_PRINTF("getaddrinfo ʧ��: %d\n", ret);
            LOG_PRINTF("���� 5 �������...\n");
            Sleep(5000);
            continue;
        }
        
        // �����׽���
        sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sock == INVALID_SOCKET) {
            LOG_PRINTF("�����׽���ʧ��: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            LOG_PRINTF("���� 5 �������...\n");
            Sleep(5000);
            continue;
        }
        
        // ���ó�ʱ
        DWORD timeout = 5000; // 5�볬ʱ
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
        
        // ���ӵ�������
        ret = connect(sock, result->ai_addr, (int)result->ai_addrlen);
        if (ret == SOCKET_ERROR) {
            LOG_PRINTF("����ʧ��: %d\n", WSAGetLastError());
            closesocket(sock);
            freeaddrinfo(result);
            LOG_PRINTF("���� 5 �������...\n");
            Sleep(5000);
            continue;
        }
        
        LOG_PRINTF("�ɹ����ӵ� %s:%s\n", host, port);
        freeaddrinfo(result);
        return sock;
    }
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG_PRINTF("�޷����ļ� %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(length + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);
    
    return content;
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    SOCKET sock;
    char* host = DEFAULT_IP;
    char* port = DEFAULT_PORT;
    char buffer[BUFFER_SIZE];
    char* message;
    int bytes_sent, bytes_received;
    int opt;
    
    // ���������в���
    while ((opt = getopt(argc, argv, "i:p:h")) != -1) {
        switch (opt) {
            case 'i':
                host = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }
    
    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LOG_PRINTF("WSAStartup ʧ��\n");
        return 1;
    }
    
    // �ȴ�2��
    Sleep(2000);
    
    while (1) {
        // ���ӵ�������
        sock = tcp_connect(host, port);
        
        while (1) {
            // ��ȡ�ļ�����
            message = read_file("file.txt");
            if (!message) {
                LOG_PRINTF("��ȡ�ļ�ʧ��\n");
                break;
            }
            
            LOG_PRINTF("������Ϣ: %s\n", message);
            
            // ��������
            bytes_sent = send(sock, message, strlen(message), 0);
            if (bytes_sent == SOCKET_ERROR) {
                LOG_PRINTF("��������ʧ��: %d\n", WSAGetLastError());
                free(message);
                break;
            }
            
            // ��������
            bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received == SOCKET_ERROR) {
                LOG_PRINTF("��������ʧ��: %d\n", WSAGetLastError());
                free(message);
                break;
            }
            
            buffer[bytes_received] = '\0';
            LOG_PRINTF("�յ��ظ�: %s\n", buffer);
            
            free(message);
            
            // ÿ��5�뷢��һ����Ϣ
            Sleep(5000);
        }
        
        closesocket(sock);
        LOG_PRINTF("���ӶϿ������� 5 �����������...\n");
        Sleep(5000);
    }
    
    WSACleanup();
    return 0;
}