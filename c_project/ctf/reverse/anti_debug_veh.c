// https://www.cnblogs.com/lordtianqiyi/articles/16471263.html
// VEH异常处理vs2010.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"


// VEH异常处理.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdio.h"

#include <windows.h>

PVOID h1;
LONG NTAPI FirstVectExcepHandler(PEXCEPTION_POINTERS pExcepInfo)
{
    if (pExcepInfo->ExceptionRecord->ExceptionCode == 0xC0000094) {
        printf("VEH异常处理\n");
        pExcepInfo->ContextRecord->Eip = pExcepInfo->ContextRecord->Eip + 3;//越过//
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
//参数1=1表示插入Veh链的头部，=0表示插入到VEH链的尾部


int main(int argc, char* argv[])
{
    h1 = AddVectoredExceptionHandler(0, &FirstVectExcepHandler);


    //构造除0异常//
    __try {

        int x = 0;
        x = x / x;
    }
    __except (1) {
        printf("SEH接管异常\n");
        RemoveVectoredExceptionHandler(h1);
    }
    printf("结束\n");
    getchar();
    return 0;
}