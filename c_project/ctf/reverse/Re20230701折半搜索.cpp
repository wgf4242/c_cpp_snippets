// Test.cpp : Defines the entry point for the console application.
// https://mp.weixin.qq.com/s/dAE_VkaAxjG4nJWc7izwEg

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
bool check()
{
	int a = 1;
	char* ptrYourFlag = (char*)((&a)+6+4*4);
	ptrYourFlag[32]=85;
	for (int i = 0; i < 32; i++)
	{
		//int tp = ptrYourFlag[i] ^ ptrYourFlag[32+i];
		if ( (char)(ptrYourFlag[i] ^ ptrYourFlag[32+i])!='c')
		{
			return false;
		}
		//printf("%c", ptrYourFlag[i]);
	}
	//	printf("\r\n");
	
	return true;
}

int main(int argc, char* argv[])
{
	/*
	char tmp[] = "693eea98fe541c1dfe428e6a799ab4b9";
	for (int i = 0; tmp[i]!=0; i++)
	{
		printf("%d, ", tmp[i]^99); 
	}*/
	char flag[64] = {
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		85,90,80, 6, 6, 2,90,91, 5, 6,86,87,82, 0,82, 7,
		 5, 6,87,81,91, 6,85, 2,84,90,90, 2, 1,87, 1,90
	}; 
	scanf("%s", flag);
	if(check())
	{
		flag[32]=0;
		printf("your flag is flag{%s}\r\n",flag);
	} else {
		printf("error flag.\r\n");
	}
	system("pause");
	return 0;
}

