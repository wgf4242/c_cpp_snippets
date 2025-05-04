#include <array>
#include <cstdint>
#include <iostream>
#include <random>

constexpr bool kDebuggerFound = true;

void test_for();

void test_auto();

template<typename T>
void auto_printContainer(const T &container);
auto auto_add(int a, int b) -> int {
    return a + b; // 返回a和b的和
}

int main() {
    // test_for();
    test_auto();

}

void test_auto() {
    // C++11中auto关键字  https://mp.weixin.qq.com/s/Ou9eVf8CRDNiBeRyQeIw8A

    // 1. 自动推断变量的类型。
    auto x = 5; // x的类型为int
    auto y = 3.14; // y的类型为double
    auto z = "Hello, world!"; // z的类型为const char*
    // 在这个例子中，auto关键字让编译器自动推断x、y和z的类型

    // for
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl; // 输出每个元素
    }

    int result = auto_add(1, 3);
    auto_printContainer(numbers); // 声明可能不对


    // 5.2 auto与引用结合使用  用于推导引用的类型
    int x1 = 10;
    auto &ref1 = x1;

    // 5.3 auto and const
    const int x2 = 10;
    auto const &ref2 = x2;

    // 5.4 auto与lambda表达式结合使用
    auto sum = [](int a, int b) { return a + b; };

}

template<typename T>
void auto_printContainer(const T &container) {
    for (const auto &element: container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void test_for() {
    std::mt19937 mt19937(kDebuggerFound ? 0x7D1 : 0x44C);

    std::array<uint8_t, 38> ctf_flag = {
            0xC2, 0x6C, 0xFC, 0xB3, 0xA7, 0x8E, 0xF5, 0x83, 0x81, 0xCB,
            0xBF, 0xD5, 0xC2, 0xCE, 0x83, 0xBD, 0xE6, 0x6A, 0xA5, 0xA8,
            0x44, 0xF5, 0x45, 0x59, 0x50, 0xD8, 0x03, 0x98, 0xF7, 0x74,
            0x87, 0xAC, 0xC5, 0x3E, 0x38, 0x2F, 0x07, 0x68};

    for (auto &v: ctf_flag) {
        v ^= mt19937();
    }

    std::cout << "flag: ";
    for (auto &v: ctf_flag) {
        std::cout << (char) (v);
    }
    std::cout << std::endl;
}
