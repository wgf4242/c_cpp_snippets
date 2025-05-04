#define _WINSOCK_DEPRECATED_NO_WARNINGS
// ������Ŀ���� - C/C++ - Ԥ��������Ԥ���������� ���_WINSOCK_DEPRECATED_NO_WARNINGS
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
    //IP_ADAPTER_INFO�ṹ��
    PIP_ADAPTER_INFO pIpAdapterInfo = NULL;
    pIpAdapterInfo = new IP_ADAPTER_INFO;

    //�ṹ���С
    unsigned long ulSize = sizeof(IP_ADAPTER_INFO);

    //��ȡ��������Ϣ
    int nRet = GetAdaptersInfo(pIpAdapterInfo, &ulSize);

    if (ERROR_BUFFER_OVERFLOW == nRet)
    {
        //�ռ䲻�㣬ɾ��֮ǰ����Ŀռ�
        delete[]pIpAdapterInfo;

        //���·����С
        pIpAdapterInfo = (PIP_ADAPTER_INFO) new BYTE[ulSize];

        //��ȡ��������Ϣ
        nRet = GetAdaptersInfo(pIpAdapterInfo, &ulSize);

        //��ȡʧ��
        if (ERROR_SUCCESS != nRet)
        {
            if (pIpAdapterInfo != NULL)
            {
                delete[]pIpAdapterInfo;
            }
            return FALSE;
        }
    }

    //MAC ��ַ��Ϣ
    char szMacAddr[20];
    //��ֵָ��
    PIP_ADAPTER_INFO pIterater = pIpAdapterInfo;
    while (pIterater)
    {
        std::cout << "�������ƣ�" << pIterater->AdapterName << std::endl;

        std::cout << "����������" << pIterater->Description << std::endl;

        sprintf_s(szMacAddr, 20, "%02X-%02X-%02X-%02X-%02X-%02X",
            pIterater->Address[0],
            pIterater->Address[1],
            pIterater->Address[2],
            pIterater->Address[3],
            pIterater->Address[4],
            pIterater->Address[5]);

        std::cout << "MAC ��ַ��" << szMacAddr << std::endl;
        std::cout << "IP��ַ�б�" << std::endl << std::endl;

        //ָ��IP��ַ�б�
        PIP_ADDR_STRING pIpAddr = &pIterater->IpAddressList;
        while (pIpAddr)
        {
            std::cout << "IP��ַ��" << pIpAddr->IpAddress.String << std::endl;
            std::cout << "�������룺" << pIpAddr->IpMask.String << std::endl;

            //ָ�������б�
            PIP_ADDR_STRING pGateAwayList = &pIterater->GatewayList;
            while (pGateAwayList)
            {
                std::cout << "���أ�" << pGateAwayList->IpAddress.String << std::endl;
                pGateAwayList = pGateAwayList->Next;
            }
            pIpAddr = pIpAddr->Next;
        }
        std::cout << std::endl << "--------------------------" << std::endl;
        pIterater = pIterater->Next;
    }

    //����
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