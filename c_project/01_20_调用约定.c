// C/C++逆向：函数逆向分析-调用约定分析 https://mp.weixin.qq.com/s/LKXyVFFW3uflkM32MBxQ4w

#include <stdio.h>

// 使用 cdecl 调用约定
int __cdecl add_cdecl(int a, int b) {
   return a + b;
}

// 使用 stdcall 调用约定
int __stdcall add_stdcall(int a, int b) {
   return a + b;
}

// 使用 fastcall 调用约定
int __fastcall add_fastcall(int a, int b) {
   return a + b;
}

int main() {
   int x = 3;
   int y = 4;

   // 调用 cdecl 函数
   int result_cdecl = add_cdecl(x, y);
   printf("cdecl result: %d\n", result_cdecl);

   // 调用 stdcall 函数
   int result_stdcall = add_stdcall(x, y);
   printf("stdcall result: %d\n", result_stdcall);

   // 调用 fastcall 函数
   int result_fastcall = add_fastcall(x, y);
   printf("fastcall result: %d\n", result_fastcall);

   return 0;
}