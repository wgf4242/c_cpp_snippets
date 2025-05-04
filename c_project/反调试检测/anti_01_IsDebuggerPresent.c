// https://mp.weixin.qq.com/s/KPOt_ezHVwSNPlyblLByXQ
// 1.jz跳转将其改为jnz
// 2.xdbg，在数据窗口使用“Ctrl+G”搜索fs:[30]+2； 将其用“Ctrl+E”将01 修改成00，
#include <stdio.h>
#include <windows.h>

BOOL CheckDebugger()
{
    // 直接调用IsDebuggerPresent函数，不需要定义额外的指针
    return IsDebuggerPresent();
}

int main(int argc, char* argv[])
{
    if (CheckDebugger())
    {
        printf("[-] 进程正在被调试 \n");
    }
    else
    {
        printf("[+] 进程没有被调试 \n");
    }

    system("pause");
    return 0;
}