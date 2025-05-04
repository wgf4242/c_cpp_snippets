#include <iostream>
#include <cmath>
#include <functional>

void divide(int dividend, int divisor, std::function<void(int, int)> callback) {
    callback(dividend / divisor, dividend % divisor);
}

void handleResult(int quotient, int remainder) {
    std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;
}

int main() {
    divide(14, 3, handleResult);
    return 0;
}
