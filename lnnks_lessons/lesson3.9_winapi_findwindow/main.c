#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
int main(void) {
	// ���� - spy++ ��  ��ⴰ��className
	if (FindWindowA("Sword2 Class", "Sword2 Window")) printf("��⵽�࿪\n");
	return 0;

}