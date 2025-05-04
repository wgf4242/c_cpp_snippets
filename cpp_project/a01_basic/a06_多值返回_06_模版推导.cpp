//C++的模版推导为开发者提供了更为灵活和简洁的代码编写方式。通过模版推导，我们可以处理不同类型的数据而无需显式指定类型。
#include <iostream>
#include <cmath>

template <typename T1, typename T2>
struct many {
    T1 quotient;
    T2 remainder;
};

template <class T1, class T2>
many(T1, T2) -> many<T1, T2>;

many<int, int> divide(int dividend, int divisor) {
    return many{
            dividend / divisor,
            dividend % divisor,
    };
}

int main() {
    auto [quotient, remainder] = divide(14, 3);
    std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;
    return 0;
}
