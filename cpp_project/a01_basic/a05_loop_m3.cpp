/*
 * CRTP
方式3基于方式2，将其改造为crtp编程风格，是不是有点看不懂了，嘿嘿。

下面struct可以被替换为class，这里我用类来描述。其实就是两个类，第一个类Print为父类，打印每次的I，并调用子类，子类PrintDerived即成Print，并将自己传递给父类，子类是一个重载类，控制递归终止。

 */
#include <iostream>

template <typename Derived, int I>
struct Print {
    Print() {
        std::cout << I << " ";
        Derived::next();
    }
};

template <int I>
struct PrintDerived : public Print<PrintDerived<I>, I> {
    static void next() { PrintDerived<I + 1>(); }
};
template <>
struct PrintDerived<100> : public Print<PrintDerived<100>, 100> {
    static void next() {}
};

int main() {
    PrintDerived<1> j;
    return 0;
}