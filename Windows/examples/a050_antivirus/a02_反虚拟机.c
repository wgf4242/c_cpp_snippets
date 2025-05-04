
#include <windows.h>
#include <stdio.h>

int IsRunningInVM() {
    char szHardware[256];
    DWORD size = sizeof(szHardware);
    int isVM = 0;

    if (RegGetValueA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\IDE", "HardwareID", RRF_RT_REG_SZ, NULL, szHardware, &size) == ERROR_SUCCESS) {
        if (strstr(szHardware, "VMware") || strstr(szHardware, "Virtual")) {
            isVM = 1;
        }
    }

    size = sizeof(szHardware);
    if (RegGetValueA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum", "0", RRF_RT_REG_SZ, NULL, szHardware, &size) == ERROR_SUCCESS) {
        if (strstr(szHardware, "VMware") || strstr(szHardware, "VBOX")) {
            isVM = 1;
        }
    }

    return isVM;
}
int main(int argc, char *argv[]) {
    if (IsRunningInVM()) {
        return 0;
    }


// RegGetValueA 被调用以从注册表路径 HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\IDE 中检索 HardwareID 的值， 如果调用成功（返回 ERROR_SUCCESS），则检查检索到的字符串（szHardware）是否包含子字符串 "VMware" 或 "Virtual" ， 如果找到任一子字符串，则将 isVM 设置为 1 ，第二个if判断同理
// 如果返回1，则代表程序在虚拟机里运行，执行退出指令