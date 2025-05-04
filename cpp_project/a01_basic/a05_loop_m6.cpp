// C++20的std::views，在std::copy时打印。
#include <iostream>
#include <iterator>
#include <ranges>

int main() {
    auto numbers = std::views::iota(1, 100 + 1);
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, "\n"));
}