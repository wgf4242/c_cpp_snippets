int main()
{
    _asm {
        xor eax, eax;
        jz s;
        add esp, 0x11; // IDA 会把此指令识别对函数堆栈进行操作，导致识别函数失败
    s:
    }
    printf("test \n");
}