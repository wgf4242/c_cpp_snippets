// https://www.bilibili.com/video/BV1oD4y1h7S3?p=39

#include <iostream>
#include "string"

using String = std::string;

class Entity {
private:
    String  m_Name;
public:
    Entity(): m_Name("Unknown") {}
    Entity(const String & name) : m_Name(name) {}

    const String& GetName() const { return m_Name; }
};

int main() {
    int a= 2;
    int* b = new int[50]; // int* = new int 一个单一的四字节，在堆上分配
    // 200 bytes = 50*4

    Entity* e = new Entity[50];
    Entity* e_1 = new Entity(); // 单一对象, () 不仅分配内存还调用构造函数
    // Entity* e_11 = (Entity*) malloc(sizeof(Entity)) // 基本和上面相似, 但仅分配内存, 不调用构造函数,

    delete e_1; // 调用了 free
    delete[] b; // 数组用 [] 删除
    std::cin.get();

    return 0;
}