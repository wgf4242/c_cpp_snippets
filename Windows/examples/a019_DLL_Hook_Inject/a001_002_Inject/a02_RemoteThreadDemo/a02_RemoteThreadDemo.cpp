// RemoteThreadDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "inject.h"



int main()
{
    CreateRemoteThreadInject(22436, LR"(D:\temp\cprojects\a01_LoadDll113_CoProjecct\dll_CoProjecct\x64\Debug\a01_GenerateDll.dll)");
}