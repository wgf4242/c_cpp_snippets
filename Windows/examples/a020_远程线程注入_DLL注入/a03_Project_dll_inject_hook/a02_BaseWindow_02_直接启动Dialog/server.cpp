#include "server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

UpdateUIFunc UpdateUI = nullptr; // 初始化为 nullptr

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"

void StartServer() {
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    char recvbuf[512];
    int recvbuflen = 512;

    iResult = recv(ClientSocket, recvbuf, recvbuflen - 1, 0); // 确保缓冲区有空间放置终止符
    if (iResult > 0) {
        recvbuf[iResult] = '\0'; // 在接收到的数据末尾添加字符串终止符
        OutputDebugStringA("Bytes received: ");
        OutputDebugStringA(std::to_string(iResult).c_str());
        OutputDebugStringA("\nData: ");
        OutputDebugStringA(recvbuf);
        OutputDebugStringA("\n");

        if (UpdateUI) { // 检查 UpdateUI 是否存在
            UpdateUI(recvbuf); // 调用 UpdateUI 函数更新界面
        }
    } else if (iResult == 0) {
        OutputDebugStringA("Connection closing...\n");
    } else {
        OutputDebugStringA("recv failed: ");
        OutputDebugStringA(std::to_string(WSAGetLastError()).c_str());
        OutputDebugStringA("\n");
    }

    closesocket(ClientSocket);
    WSACleanup();
}