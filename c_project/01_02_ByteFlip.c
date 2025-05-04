#include "assert.h"

unsigned char Flip(unsigned char x) {
    x = ((x & 0x55) << 1) | ((x & 0xaa) >> 1);
    x = ((x & 0x33) << 2) | ((x & 0xcc) >> 2);
    x = ((x & 0x0f) << 4) | ((x & 0xf0) >> 4);
    return x;
}

int main(void) {
    // 比如把0x40变成0x02,0x82变成0x41??
    // 10000010 => 01000001
    assert(Flip('\x82') == '\x41');
    // printf("%x", b);
    return 0;
}
