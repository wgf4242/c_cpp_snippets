#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
int main(void) {
	unsigned Pid;
	const unsigned HpAddress = 0x09B42558;
	const float  Hp = 1000.0f;
	unsigned Writed = 0;
	printf("��������Ϸ�Ľ���ID:\r\n");
	scanf("%d", &Pid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
	
	if (!hGame) {
		printf("��Ϸ���̴�ʧ��");
		return 0;
	}
	
	while (1) {
		Sleep(100);
		WriteProcessMemory(hGame, HpAddress, &Hp, sizeof(Hp), &Writed);
	}
	return 0;

}