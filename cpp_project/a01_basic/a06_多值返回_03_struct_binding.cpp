//对上面进行改造，C++17引入的结构化绑定进一步简化了多值返回的代码。使用auto和结构化绑定，使得代码更加直观易懂。
//如果面试官要你进一步的对上面的方法进行改造，那么可以变为下面这个代码示例，使用结构化绑定使代码更加优雅。
#include <iostream>
#include <cmath>

auto divide(int dividend, int divisor) {
    struct result {
        int quotient;
        int remainder;
    };
    return result{dividend / divisor, dividend % divisor};
}

int main() {
    auto [quotient, remainder] = divide(14, 3);
    std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;
    return 0;
}
