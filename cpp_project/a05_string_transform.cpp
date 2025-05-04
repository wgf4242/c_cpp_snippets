#include <gtest/gtest.h>
using namespace std;

TEST(TRANSFORM, transform_int) {
    vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 transform 将每个元素加倍
    transform(vec.begin(), vec.end(), vec.begin(),
                   [](int x) { return x * 2; });

    // 输出结果
    for (int x: vec) {
        cout << x << " "; // 输出: 2 4 6 8 10
    }
}

TEST(TRANSFORM, transform_str) {
    char str[] = "hello";

    // 使用 transform 将小写转换为大写
    transform(str, str + 5, str,
                   [](char c) { return toupper(c); });

    // 输出结果
    cout << str << endl; // 输出: HELLO
}
