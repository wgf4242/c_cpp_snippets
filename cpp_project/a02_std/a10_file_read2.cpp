#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip> // for std::hex

void printFileContentInHex(const std::string& filename) {
    std::ifstream inputFile(filename, std::ios::binary); // 以二进制模式打开文件，避免对内容进行任何转换
    if (!inputFile) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    // 将文件内容读入到字符串中
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    // 遍历字符串并打印每个字符的16进制值
    for (unsigned char c : content) { // 使用 unsigned char 以确保正确处理字符值
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)c << " ";
    }
    std::cout << std::endl; // 打印结束后换行
}

int main() {
    printFileContentInHex("out.txt");
    return 0;
}