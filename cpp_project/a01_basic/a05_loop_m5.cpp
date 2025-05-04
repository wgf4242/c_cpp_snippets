// 使用算法库 std::for_each简单粗暴。
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    std::vector<int> l(100);
    std::iota(l.begin(), l.end(), 1);
    std::for_each(l.begin(), l.end(), [](int& n) { std::cout << n << std::endl; });
    return 0;
}