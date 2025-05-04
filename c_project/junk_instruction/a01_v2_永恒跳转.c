// 永恒跳转
int main()
{
    _asm {
    xor eax, eax;// eax ^ eax = 0 
    jz s; // 必然成立跳转，一定会跳转
    _emit 0x11; //填充垃圾指令 byte类型
    _emit 0x22; //填充垃圾指令 byte类型
    _emit 0x33; //填充垃圾指令 byte类型
    s:
    }
    printf("test \n");
}