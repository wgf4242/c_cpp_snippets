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
#include <Windows.h>

int main()
{
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    if (GetAdaptersInfo(NULL, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            // pAdapter->Description中包含"PCI"的为物理网卡;pAdapter->Type是71的为无线网卡
            if (strstr(pAdapter->Description, "PCI") != nullptr || pAdapter->Type == 71)
            {
                printf("------------------------------\n");
                printf("AdapterName: \t%s\n", pAdapter->AdapterName);
                printf("AdapterDesc: \t%s\n", pAdapter->Description);
                printf("AdapterAddr: \t");
                for (UINT i = 0; i < pAdapter->AddressLength; i++)
                {
                    printf("%X%c", pAdapter->Address[i],
                        i == pAdapter->AddressLength - 1 ? '\n' : '-');
                }
                printf("AdapterType: \t%d\n", pAdapter->Type);
                printf("IPAddress: \t%s\n",
                    pAdapter->IpAddressList.IpAddress.String);
                printf("IPMask: \t%s\n", pAdapter->IpAddressList.IpMask.String);
            }
            pAdapter = pAdapter->Next;
        }
    }
    else
    {
        printf("Callto GetAdaptersInfo failed.\n");
    }
    system("pause");
    return 0;
}