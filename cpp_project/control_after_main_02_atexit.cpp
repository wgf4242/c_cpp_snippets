// 2. atexit()函数
#include <iostream>
#include <cstdlib>

void func() {
    std::cout << "atexit函数被调用" << std::endl;
}

int main() {
    atexit(func);
    std::cout << "main函数结束" << std::endl;
    return 0;
}