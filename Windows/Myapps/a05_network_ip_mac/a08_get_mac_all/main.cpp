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

BOOL GetLocalAdaptersInfo()
{
    //IP_ADAPTER_INFO结构体
    PIP_ADAPTER_INFO pIpAdapterInfo = NULL;
    pIpAdapterInfo = new IP_ADAPTER_INFO;

    //结构体大小
    unsigned long ulSize = sizeof(IP_ADAPTER_INFO);

    //获取适配器信息
    int nRet = GetAdaptersInfo(pIpAdapterInfo, &ulSize);

    if (ERROR_BUFFER_OVERFLOW == nRet)
    {
        //空间不足，删除之前分配的空间
        delete[]pIpAdapterInfo;

        //重新分配大小
        pIpAdapterInfo = (PIP_ADAPTER_INFO) new BYTE[ulSize];

        //获取适配器信息
        nRet = GetAdaptersInfo(pIpAdapterInfo, &ulSize);

        //获取失败
        if (ERROR_SUCCESS != nRet)
        {
            if (pIpAdapterInfo != NULL)
            {
                delete[]pIpAdapterInfo;
            }
            return FALSE;
        }
    }

    //MAC 地址信息
    char szMacAddr[20];
    //赋值指针
    PIP_ADAPTER_INFO pIterater = pIpAdapterInfo;
    while (pIterater)
    {
        std::cout << "网卡名称：" << pIterater->AdapterName << std::endl;

        std::cout << "网卡描述：" << pIterater->Description << std::endl;

        sprintf_s(szMacAddr, 20, "%02X-%02X-%02X-%02X-%02X-%02X",
            pIterater->Address[0],
            pIterater->Address[1],
            pIterater->Address[2],
            pIterater->Address[3],
            pIterater->Address[4],
            pIterater->Address[5]);

        std::cout << "MAC 地址：" << szMacAddr << std::endl;
        std::cout << "IP地址列表：" << std::endl << std::endl;

        //指向IP地址列表
        PIP_ADDR_STRING pIpAddr = &pIterater->IpAddressList;
        while (pIpAddr)
        {
            std::cout << "IP地址：" << pIpAddr->IpAddress.String << std::endl;
            std::cout << "子网掩码：" << pIpAddr->IpMask.String << std::endl;

            //指向网关列表
            PIP_ADDR_STRING pGateAwayList = &pIterater->GatewayList;
            while (pGateAwayList)
            {
                std::cout << "网关：" << pGateAwayList->IpAddress.String << std::endl;
                pGateAwayList = pGateAwayList->Next;
            }
            pIpAddr = pIpAddr->Next;
        }
        std::cout << std::endl << "--------------------------" << std::endl;
        pIterater = pIterater->Next;
    }

    //清理
    if (pIpAdapterInfo)
    {
        delete[]pIpAdapterInfo;
    }

    return TRUE;
}

int main()
{
    GetLocalAdaptersInfo();
    std::cin.get();
    system("pause");
    return 0;
}