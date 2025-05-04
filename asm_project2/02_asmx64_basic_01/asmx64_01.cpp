#include<Windows.h>
#include <iostream>
using namespace std;

EXTERN_C DWORD myAdd(DWORD u1, DWORD u2);
EXTERN_C DWORD myAdd1(DWORD u1, DWORD u2);
// myAdd1: a+b+1

int main()
{
    DWORD ret = myAdd(120, 240);
    cout << ret << endl;

    cout << myAdd1(12, 24) << endl;
    return 0;
}
