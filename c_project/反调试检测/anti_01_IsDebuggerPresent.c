// https://mp.weixin.qq.com/s/KPOt_ezHVwSNPlyblLByXQ
// 1.jz��ת�����Ϊjnz
// 2.xdbg�������ݴ���ʹ�á�Ctrl+G������fs:[30]+2�� �����á�Ctrl+E����01 �޸ĳ�00��
#include <stdio.h>
#include <windows.h>

BOOL CheckDebugger()
{
    // ֱ�ӵ���IsDebuggerPresent����������Ҫ��������ָ��
    return IsDebuggerPresent();
}

int main(int argc, char* argv[])
{
    if (CheckDebugger())
    {
        printf("[-] �������ڱ����� \n");
    }
    else
    {
        printf("[+] ����û�б����� \n");
    }

    system("pause");
    return 0;
}