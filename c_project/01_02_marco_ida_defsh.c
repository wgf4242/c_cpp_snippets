// def.h test
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
int main() {
    setbuf(stdout, NULL);
    unsigned int a = 0x12345678; // 78 56 34 12
    assert(LOBYTE(a)==0x78);
    assert(BYTE1(a) ==0x56);
    assert(BYTE2(a) ==0x34);
    assert(HIBYTE(a)==0x12);
    unsigned long swap = _byteswap_ulong(a); // 12 34 56 78
    assert(LOBYTE(swap)==0x12);
    assert(BYTE1(swap) ==0x34);
    assert(BYTE2(swap) ==0x56);
    assert(HIBYTE(swap)==0x78);
    return 0;
}