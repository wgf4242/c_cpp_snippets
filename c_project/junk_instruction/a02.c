int main()
{
 _asm {
  push eax;
  add esp, 4;//这里代替了pop从而保证栈推平衡
 }
printf("Hello \n");
}