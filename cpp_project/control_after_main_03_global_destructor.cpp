// 3.全局对象和静态对象的析构函数
#include <iostream>

class Test {
public:
    ~Test() {
        std::cout << "全局对象的析构函数被调用" << std::endl;
    }
};

Test t;

int main() {
    std::cout << "main函数结束" << std::endl;
    return 0;
}