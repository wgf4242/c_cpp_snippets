// Tuple和tie的组合为函数返回多个值提供了一种简洁的方式。通过使用std::tie，我们可以将tuple中的元素解包到不同的变量中，提高代码的清晰度。
// 这种方法算是标准答案之一，比较简单清晰，如果返回值是两个pair也可以。
#include <iostream>
#include <tuple>
#include <cmath>

std::tuple<int, int> divide(int dividend, int divisor) {
    return std::make_tuple(dividend / divisor, dividend % divisor);
}

int main() {
    int quotient, remainder;
    std::tie(quotient, remainder) = divide(14, 3);
    std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;
    return 0;
}
