#include <stdio.h>
#include <libio.h>

void myPrintf(char* string){
 printf("%s:\t", "NoHook");
 printf("%s\n", string);
}

void myPrintfPlus(char *string){
 printf("%s:\t", "Hook");
 printf("%s\n", string);
}

int main(int argc, char const *argv[])
{
 void (*myPrintf)(char*) = myPrintfPlus;
 myPrintf("test");

 return 0;
}