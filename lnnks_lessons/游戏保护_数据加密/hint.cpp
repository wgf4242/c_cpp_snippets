#include "hint.h"

// 5000 * 4 // 20000
hint::hint(int val) {
    mem[0] = new char;
    mem[1] = new char;
    mem[2] = new char;
    mem[3] = new char;

    *this = val;
}

hint::~hint() {
    delete mem[0];
    delete mem[1];
    delete mem[2];
    delete mem[3];
}

hint::operator int() {
    int val;
    char* read = (char*)&val;

    read[3] = mem[0][0];
    read[1] = mem[1][0];
    read[0] = mem[2][0] ^ 0x23;
    read[2] = mem[3];

    return val;
}

void hint::operator=(int val) {
    char* read = (char*)&val;
    mem[0] = read[3];
    mem[1] = read[1];
    mem[2] = read[0] ^ 0x23;
    mem[3] = read[2];

}

// 1 1 1  1
// 1 + 500 - 500