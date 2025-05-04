// https://mp.weixin.qq.com/s/VEvUxpcJPsxT9kL7-zLTxg
#include <iostream>

void divideWithReferences(int dividend, int divisor, int& quotient, int& remainder) {
    quotient = dividend / divisor;
    remainder = dividend % divisor;
}

void divideWithPointers(int dividend, int divisor, int* quotient, int* remainder) {
    if (quotient) *quotient = dividend / divisor;
    if (remainder) *remainder = dividend % divisor;
}

int main() {
    int quotient_ref, remainder_ref;
    divideWithReferences(14, 3, quotient_ref, remainder_ref);
    std::cout << "Quotient (with references): " << quotient_ref << ", Remainder (with references): " << remainder_ref << std::endl;

    int quotient_ptr, remainder_ptr;
    divideWithPointers(14, 3, &quotient_ptr, &remainder_ptr);
    std::cout << "Quotient (with pointers): " << quotient_ptr << ", Remainder (with pointers): " << remainder_ptr << std::endl;
    return 0;
}
