//自定义out是一种通过结构体包装的方式，将输出参数作为结构体的成员。这种方式提高了代码的可读性，尤其适用于需要返回多个值的函数。
#include <iostream>
#include <cmath>
#include <functional>

template <class T>
struct out {
    std::function<void(T)> target;

    out(T* t)
            : target([t](T&& in) {
        if (t) *t = std::move(in);
    }) {}

    template <class... Args>
    void emplace(Args&&... args) {
        target(T(std::forward<Args>(args)...));
    }

    template <class X>
    void operator=(X&& x) {
        emplace(std::forward<X>(x));
    }

    template <class... Args>
    void operator()(Args&&... args) {
        emplace(std::forward<Args>(args)...);
    }
};

void divide(int dividend, int divisor, out<int>& quotient_out, out<int>& remainder_out) {
    quotient_out.emplace(dividend / divisor);
    remainder_out.emplace(dividend % divisor);
}

int main() {
    int quotient, remainder;
    out<int> quotient_out(&quotient);
    out<int> remainder_out(&remainder);

    divide(14, 3, quotient_out, remainder_out);

    std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;

    return 0;
}
