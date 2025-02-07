int main()
{
 _asm {
  xor eax, eax;
  jz s;// 这里一定会跳转
  _emit 0x11;
  _emit 0x22;
  _emit 0x33;// 0x33是xor指令的操作码，会导致后面正常的Push指令被错误解析
 s:
 }
    printf("Hello \n");
}