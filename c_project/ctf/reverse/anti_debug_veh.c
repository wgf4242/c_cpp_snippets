// https://www.cnblogs.com/lordtianqiyi/articles/16471263.html
// VEH�쳣����vs2010.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"


// VEH�쳣����.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdio.h"

#include <windows.h>

PVOID h1;
LONG NTAPI FirstVectExcepHandler(PEXCEPTION_POINTERS pExcepInfo)
{
    if (pExcepInfo->ExceptionRecord->ExceptionCode == 0xC0000094) {
        printf("VEH�쳣����\n");
        pExcepInfo->ContextRecord->Eip = pExcepInfo->ContextRecord->Eip + 3;//Խ��//
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
//����1=1��ʾ����Veh����ͷ����=0��ʾ���뵽VEH����β��


int main(int argc, char* argv[])
{
    h1 = AddVectoredExceptionHandler(0, &FirstVectExcepHandler);


    //�����0�쳣//
    __try {

        int x = 0;
        x = x / x;
    }
    __except (1) {
        printf("SEH�ӹ��쳣\n");
        RemoveVectoredExceptionHandler(h1);
    }
    printf("����\n");
    getchar();
    return 0;
}