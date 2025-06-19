#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <getopt.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define DEFAULT_IP "10.63.81.34"
#define DEFAULT_PORT "9999"

void print_usage(const char* program_name) {
    printf("用法: %s [选项]\n", program_name);
    printf("选项:\n");
    printf("  -i <IP>     服务器 IP 地址 (默认: %s)\n", DEFAULT_IP);
    printf("  -p <端口>   服务器端口 (默认: %s)\n", DEFAULT_PORT);
    printf("  -h          显示此帮助信息\n");
    printf("\n示例:\n");
    printf("  %s -i 101.201.56.60 -p 8090\n", program_name);
}

SOCKET tcp_connect(const char* host, const char* port) {
    SOCKET sock;
    struct addrinfo hints, *result;
    int ret;
    
    while (1) {
        printf("尝试连接到 %s:%s...\n", host, port);
        
        // 初始化hints结构
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        
        // 获取地址信息
        ret = getaddrinfo(host, port, &hints, &result);
        if (ret != 0) {
            printf("getaddrinfo 失败: %d\n", ret);
            printf("将在 5 秒后重试...\n");
            Sleep(5000);
            continue;
        }
        
        // 创建套接字
        sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sock == INVALID_SOCKET) {
            printf("创建套接字失败: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            printf("将在 5 秒后重试...\n");
            Sleep(5000);
            continue;
        }
        
        // 设置超时
        DWORD timeout = 5000; // 5秒超时
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
        
        // 连接到服务器
        ret = connect(sock, result->ai_addr, (int)result->ai_addrlen);
        if (ret == SOCKET_ERROR) {
            printf("连接失败: %d\n", WSAGetLastError());
            closesocket(sock);
            freeaddrinfo(result);
            printf("将在 5 秒后重试...\n");
            Sleep(5000);
            continue;
        }
        
        printf("成功连接到 %s:%s\n", host, port);
        freeaddrinfo(result);
        return sock;
    }
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件 %s\n", filename);
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
    
    // 解析命令行参数
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
    
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup 失败\n");
        return 1;
    }
    
    // 等待2秒
    Sleep(2000);
    
    while (1) {
        // 连接到服务器
        sock = tcp_connect(host, port);
        
        while (1) {
            // 读取文件内容
            message = read_file("file.txt");
            if (!message) {
                printf("读取文件失败\n");
                break;
            }
            
            printf("发送消息: %s\n", message);
            
            // 发送数据
            bytes_sent = send(sock, message, strlen(message), 0);
            if (bytes_sent == SOCKET_ERROR) {
                printf("发送数据失败: %d\n", WSAGetLastError());
                free(message);
                break;
            }
            
            // 接收数据
            bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received == SOCKET_ERROR) {
                printf("接收数据失败: %d\n", WSAGetLastError());
                free(message);
                break;
            }
            
            buffer[bytes_received] = '\0';
            printf("收到回复: %s\n", buffer);
            
            free(message);
            
            // 每隔5秒发送一次消息
            Sleep(5000);
        }
        
        closesocket(sock);
        printf("连接断开，将在 5 秒后重新连接...\n");
        Sleep(5000);
    }
    
    WSACleanup();
    return 0;
}