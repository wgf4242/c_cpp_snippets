//https://mp.weixin.qq.com/s/C1cR4XWK2dpUo9ARnLDmDA
// 模版重载 使用模版与特化来处理，当迭代100时只输出100，否则输出I，并且+1递归处理。
#include <iostream>

template<int I>
struct JustPrint : public JustPrint<I + 1> {
    JustPrint() : JustPrint<I + 1>() { std::cout << I << " "; }
};

template<>
struct JustPrint<100> {
    JustPrint<100>() { std::cout << 1 << " "; }
};

int main() {
    JustPrint<1> j;
}