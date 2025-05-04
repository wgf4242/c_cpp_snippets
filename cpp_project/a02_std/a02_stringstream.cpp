// 调试编译 g++ -g -o myprogram a02_stringstream.cpp
#include <iostream>
#include <sstream> // 包含 sstream 头文件以使用 stringstream

int main() {
    std::stringstream stream; // 创建一个字符串流对象
    int v6;

    // 直接从 cin 读取并写入到 stream
    for (int i = 0; i <= 4; ++i) {
        std::cin >> v6;
        stream << v6 << " "; // 将读取的整数写入流，并添加一个空格
    }

    // 打印最终的字符串流内容
    std::cout << "最终字符串流内容: " << stream.str() << std::endl;

    return 0;
}