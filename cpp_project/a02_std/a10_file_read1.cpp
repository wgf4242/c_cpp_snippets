// 先写个 out.txt 内容 > 4字符
#include <print>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


std::string readFile(const std::string& filePath) {
    // 使用ifstream打开文件
    std::ifstream inputFile(filePath, std::ios::binary | std::ios::ate);

    // 检查文件是否成功打开
    if (!inputFile) {
        std::cerr << "无法打开文件: " << filePath << std::endl;
        return {}; // 返回空字符串
    }

    // 获取文件大小
    std::streamsize fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // 定义一个string来保存文件内容
    std::string buffer(static_cast<std::size_t>(fileSize), '\0');

    // 读取文件内容到string
    if (inputFile.read(&buffer[0], fileSize)) {
        // 成功读取
    }
    else {
        std::cerr << "读取文件失败" << std::endl;
        return {}; // 返回空字符串
    }

    // 关闭文件
    inputFile.close();

    return buffer;
}



int main(int argc, char* argv[]) {

    auto compressed = readFile("out.txt");
    
    // 删除 main 逻辑中的前面四个字节（长度）
    compressed.erase(0, 4);
    std::println("{}", compressed);

}