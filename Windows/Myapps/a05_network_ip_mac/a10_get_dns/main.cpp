#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <atlstr.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#include <Windows.h>

int main()
{
    DWORD nLength = 0;
    //先获取实际大小，并存入nLength
    if (GetNetworkParams(NULL, &nLength) != ERROR_BUFFER_OVERFLOW)
    {
        return -1;
    }
    //根据实际所需大小，分配空间
    FIXED_INFO* pFixedInfo = (FIXED_INFO*)new BYTE[nLength];

    //获得本地计算机网络参数
    if (GetNetworkParams(pFixedInfo, &nLength) != ERROR_SUCCESS)
    {
        delete[] pFixedInfo;
        return -1;
    }

    //获得本地计算机DNS服务器地址
    char strText[500] = "本地计算机的DNS地址：\n";
    IP_ADDR_STRING* pCurrentDnsServer = &pFixedInfo->DnsServerList;
    while (pCurrentDnsServer != NULL)
    {
        char strTemp[100] = "";
        sprintf(strTemp, "%s\n", pCurrentDnsServer->IpAddress.String);
        strcat(strText, strTemp);
        pCurrentDnsServer = pCurrentDnsServer->Next;
    }
    puts(strText);
    delete[] pFixedInfo;

    system("pause");
    return 0;
}