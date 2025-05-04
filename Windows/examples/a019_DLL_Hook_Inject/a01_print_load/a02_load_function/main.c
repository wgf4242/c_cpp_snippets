#include <stdio.h>
#include <windows.h>

// ���庯��ָ�����ͣ�Ҫ����ʵ��DLL�к����Ĳ����ͷ���ֵ�������޸�
typedef int(*MYFUNCTIONTYPE)(int, int);

int main() {
	HMODULE hModule = LoadLibrary(TEXT("a01_print_01.dll"));
	if (hModule == NULL) {
		// ����ʧ�ܣ����������Ϣ�����ش�����
		printf("�޷����ض�̬���ӿ�\n");
		return 1;
	}

	// ��ȡ��ΪMyFunction������DLL�к�����������֣��谴ʵ�ʸģ��ĺ�����ַ
	MYFUNCTIONTYPE pMyFunction = (MYFUNCTIONTYPE)GetProcAddress(hModule, "add");
	if (pMyFunction == NULL) {
		// ��ȡ������ַʧ�ܵĴ���
		printf("�޷���ȡ������ַ\n");
		FreeLibrary(hModule);
		return 1;
	}

	// ���ú������������������ʾ����������������������ʵ�ʺ���Ҫ�����
	int result = pMyFunction(5, 3);
	printf("�������ý��: %d\n", result);

	FreeLibrary(hModule);
	return 0;
}