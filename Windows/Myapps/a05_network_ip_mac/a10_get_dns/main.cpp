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
    //�Ȼ�ȡʵ�ʴ�С��������nLength
    if (GetNetworkParams(NULL, &nLength) != ERROR_BUFFER_OVERFLOW)
    {
        return -1;
    }
    //����ʵ�������С������ռ�
    FIXED_INFO* pFixedInfo = (FIXED_INFO*)new BYTE[nLength];

    //��ñ��ؼ�����������
    if (GetNetworkParams(pFixedInfo, &nLength) != ERROR_SUCCESS)
    {
        delete[] pFixedInfo;
        return -1;
    }

    //��ñ��ؼ����DNS��������ַ
    char strText[500] = "���ؼ������DNS��ַ��\n";
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