// C++20的std::views，在std::copy时打印。
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
    auto range = std::views::transform(std::ranges::iota_view{1, 101}, [](const auto& x) {
        std::cout << x << std::endl;
        return x;
    });
    std::vector<int> a(range.begin(), range.end());
}