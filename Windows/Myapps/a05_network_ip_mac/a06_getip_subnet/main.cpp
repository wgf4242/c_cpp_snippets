#define _WINSOCK_DEPRECATED_NO_WARNINGS
// 或在项目属性 - C/C++ - 预处理器，预处理器定义 添加_WINSOCK_DEPRECATED_NO_WARNINGS
//https ://blog.csdn.net/morningstar929/article/details/101024153/

#include <iostream>
#include <atlstr.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")

int main()
{
    CString szMark;
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    //第一次调用GetAdaptersInfo获取ulOutBufLen大小
    if (GetAdaptersInfo(NULL, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
    }
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            PIP_ADDR_STRING pIPAddr;
            pIPAddr = &pAdapter->IpAddressList;
            while (pIPAddr)
            {
                std::cout << "IP：" << pIPAddr->IpAddress.String << std::endl;
                std::cout << "Mask：" << pIPAddr->IpMask.String << std::endl;
                std::cout << std::endl;
                pIPAddr = pIPAddr->Next;
            }
            pAdapter = pAdapter->Next;
        }
    }
    if (pAdapterInfo)
    {
        free(pAdapterInfo);
    }

    system("pause");
    return 0;
}