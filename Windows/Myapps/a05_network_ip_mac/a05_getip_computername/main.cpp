#define _WINSOCK_DEPRECATED_NO_WARNINGS
// ������Ŀ���� - C/C++ - Ԥ��������Ԥ���������� ���_WINSOCK_DEPRECATED_NO_WARNINGS
//https ://blog.csdn.net/morningstar929/article/details/101024153/
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#include <Windows.h>

int main()
{
    int wVersionRequested = MAKEWORD(2, 2);
    WSADATA lpWSAData;
    WSAStartup(wVersionRequested, &lpWSAData);
    //��ȡ������
    char szHostName[128];
    if (gethostname(szHostName, 128) == 0)
    {
        std::cout << "���ؼ���������ǣ�" << szHostName << std::endl;
    }
    //��ȡ����IP��ַ
    struct hostent* pHost;
    pHost = gethostbyname(szHostName);
    for (size_t i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
    {
        std::cout << "����IP��ַ�ǣ�" << inet_ntoa(*(struct in_addr*)pHost->h_addr_list[i]) << std::endl;
    }

    WSACleanup();
    system("pause");
    return 0;
}