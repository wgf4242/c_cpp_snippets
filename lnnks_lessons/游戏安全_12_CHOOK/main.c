
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
//B020000 - 81 FE 08EF4C00 - cmp esi, Sword2UI.exe + CEF08
//B020000 - 75 02 - jne 0B02000A
//B020000 - 31 FF - xor edi, edi
//B020000 - 29 7E 10 - sub[esi + 10], edi
//B020000 - 8B 46 10 - mov eax, [esi + 10]
//B020000 - E9 A3FD3FF5 - jmp Sword2UI.exe + 1FDB8

char wudiCode[] = {
0x81, 0xFE,0x08,0xEF,0x4C,0x00,//cmp esi,4cef08
0x75,0x02,//jne
0x31,0xFF,//xor edi,edi
0x29, 0x7E, 0x10,//sub[esi + 10], edi
0x8B,0x46,0x10,//mov eax, [esi + 10]
0xE9,0x00,0x00, 0x00, 0x00,0x90//jmp
};

int main(void) {
	unsigned Pid;
	printf("请输入游戏进程ID:\r\n");
	scanf("%d", &Pid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
	if (hGame) {
		LPVOID wudiCodeA = VirtualAllocEx(hGame, NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (wudiCodeA) {
			unsigned* Read = wudiCode + sizeof(wudiCode) - 5;
			Read[0] = 0x41fdb8 - ((unsigned)wudiCodeA + sizeof(wudiCode) - 0x6) - 0x5;
			BOOL BRet = WriteProcessMemory(hGame, wudiCodeA, wudiCode, sizeof(wudiCode),  NULL);
			if (BRet)
			{
				printf("HOOK无敌成功!");
				while (1);
			}
			else printf("HOOK启动失败");
		}
		else  printf("为HOOK代码分配内存失败！请检查内存情况, 以及是否存在驱动过滤保护！");
	}
	else printf("打开游戏进程失败!, 请检查输入的游戏进程ID!");

	return 0;

}