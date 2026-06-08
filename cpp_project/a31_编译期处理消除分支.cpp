// C++编程实践—解决if分支的具体的方法 https://mp.weixin.qq.com/s/HjRZeqIHyLVaG-1LSuijow
// cl /EHsc /std:c++latest a.cpp
// g++ -std=gnu++2a a.cpp
// visual studio 预览 - 最新 C++ 工作草案中的功能 (/std:c++latest)
#include <variant>
#include <iostream>
#include <type_traits>
#include <iomanip>
#include <vector>


template<class T> struct always_false : std::false_type {};

using var_t = std::variant<int, long, double, std::string>;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    std::vector<var_t> vec = { 10, 15l, 1.5, "hello" };
    for (auto& v : vec) {
        // void visitor, only called for side-effects
        std::visit([](auto&& arg) {std::cout << arg; }, v);

        // value-returning visitor. A common idiom is to return another variant
        var_t w = std::visit([](auto&& arg) -> var_t {return arg + arg; }, v);

        std::cout << ". After doubling, variant holds ";
        // type-matching visitor: can also be a class with 4 overloaded operator()'s
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, long>)
                std::cout << "long with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, double>)
                std::cout << "double with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "std::string with value " << std::quoted(arg) << '\n';
            else
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
            }, w);
    }

    for (auto& v : vec) {
        std::visit(overloaded{
            [](int arg) { std::cout << arg << ' '; },
            [](long arg) { std::cout << arg << ' '; },
            [](double arg) { std::cout << arg << ' '; },
            [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; },
            }, v);
    }
}