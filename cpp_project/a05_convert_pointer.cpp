#include <iostream>

int main() {
    unsigned int a[] = {0x63656F6D, 0x637B6674, 0x34346635, 0x2D323363, 0x39626263, 0x3434342D, 0x65612D65, 0x632D3466, 0x37616630, 0x36613763, 0x7D613762};
    char *bytes =(char*)a;
    // auto *bytes = (unsigned char *)(a);
    // unsigned char *bytes = reinterpret_cast<unsigned char *>(a);
    for (int i = 0; i < 44; i++) {
        printf("%c", bytes[i]);
    }
    std::cout << std::endl;
    return 0;
}