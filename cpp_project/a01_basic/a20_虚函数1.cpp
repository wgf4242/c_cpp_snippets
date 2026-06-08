/*
cl /EHsc virtual_func.cpp

基类的虚函数就像 “接口规范”，规定了函数的名称、参数、返回值；
派生类重写虚函数就是 “具体实现”，不同派生类可以有不同的实现逻辑；
调用时会自动匹配 “实际对象” 的实现，而非 “指针类型” 的实现。
*/
#include <iostream>
using namespace std;

// 基类：动物
class Animal {
public:
    // 声明虚函数：发出叫声
    virtual void makeSound() {
        cout << "动物发出未知叫声" << endl;
    }

    // 虚析构函数：避免内存泄漏（重要！）, 不写virtual时只执行基类析构，不会执行派生类析构
    virtual ~Animal() {}
};

// 派生类：猫
class Cat : public Animal {
public:
    // 重写基类的虚函数（override可选，但推荐）
    void makeSound() override {
        cout << "喵呜~" << endl;
    }
};

// 派生类：狗
class Dog : public Animal {
public:
    // 重写基类的虚函数
    void makeSound() override {
        cout << "汪汪！" << endl;
    }
};

int main() {
    // 基类指针指向不同派生类对象
    Animal* animal1 = new Cat();
    Animal* animal2 = new Dog();
    Animal* animal3 = new Animal();

    // 调用虚函数：根据实际对象类型执行
    animal1->makeSound(); // 输出：喵呜~
    animal2->makeSound(); // 输出：汪汪！
    animal3->makeSound(); // 输出：动物发出未知叫声

    // 释放内存
    delete animal1;
    delete animal2;
    delete animal3;

    return 0;
}