#include <windows.h>
#include <stdio.h>

int main() {
    // ����һ���ڴ�
    int* pMemory = (int*)VirtualAlloc(NULL, sizeof(int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (pMemory == NULL) {
        printf("�ڴ����ʧ�ܡ�\n");
        return 1;
    }

    // ������д���ڴ�
    *pMemory = 42;
    printf("��ʼֵ: %d\n", *pMemory);

    // �����ڴ汣������Ϊֻ��
    DWORD oldProtect;
    if (VirtualProtect(pMemory, sizeof(int), PAGE_READONLY, &oldProtect)) {
        printf("�ڴ汣�������Ѹ���Ϊֻ����\n");
    }
    else {
        printf("�޷������ڴ汣�����ԡ�\n");
        VirtualFree(pMemory, 0, MEM_RELEASE);
        return 1;
    }

    // ����д��ֻ���ڴ棨�⽫���³��������
    __try {
        *pMemory = 100;  // �����ڴ�������ֻ���ģ�����д��ᴥ�����ʳ�ͻ
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        printf("д��ֻ���ڴ�ʱ�����쳣��\n");
    }

    // �����ڴ汣�����Իؿɶ�д
    if (VirtualProtect(pMemory, sizeof(int), oldProtect, &oldProtect)) {
        *pMemory = 100;
        printf("��ֵ: %d\n", *pMemory);
    }

    // �ͷ��ڴ�
    VirtualFree(pMemory, 0, MEM_RELEASE);
    return 0;
}
