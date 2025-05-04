// https://mp.weixin.qq.com/s/Bf1ek-rPzHR5MQG963IZyA
// 1. 析构函数
#include <iostream>

class Test {
public:
    ~Test() {
        std::cout << "析构函数被调用" << std::endl;
    }
};

int main() {
    Test t;
    std::cout << "main函数结束" << std::endl;
    return 0;
}