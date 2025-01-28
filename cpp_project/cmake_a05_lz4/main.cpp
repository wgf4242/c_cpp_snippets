#include <cstdint>
#include <locale>
#include <print>
#include <string>
#include <fstream>

#include <lz4.h>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len) //初始化函数
{
    int           i = 0, j = 0;
    unsigned char k[256] = { 0 };
    unsigned char tmp = 0;
    for (i = 0; i < 256; i++) {
        s[i] = i;
        k[i] = key[i % Len];
    }
    for (i = 0; i < 256; i++) {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j]; //交换s[i]和s[j]
        s[j] = tmp;
    }
}

void showBox(unsigned char* s) {
    while (*s) { // 遍历直到遇到空字符
        printf("%02X ", *s); // 使用printf以16进制格式打印，%02X表示两位十六进制数，不足两位前面补0
        ++s;
    }
    std::cout << std::endl; // 换行以便于阅读输出
}

void rc4_crypt(unsigned char* s, std::string& Data) //加解密
{
    int           i = 0, j = 155 /* !? */, t = 0;
    unsigned long k = 0;

    // 其实这两个不需要添加，但是要改一下 Data[k+2] 为 Data[k]，然后循环次数也要改一下
    Data.insert(0, 1, '$');
    Data.insert(0, 1, ' ');

    std::string dec(Data.size() - 2, '\0');
    for (k = 0; k < Data.size() - 2; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        std::ranges::swap(s[i], s[j]);
        t = (s[i] + s[j]) % 256;
        //dec[k] = Data[k] ^ s[t];

        //printf("%d,", j);
        dec[k] = Data[k + 2] ^ s[t];
    }

    std::println("{}", dec);
}

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
    //auto compressed = content;

    // 删除 main 逻辑中的前面四个字节（长度）
    compressed.erase(0, 4);

    std::string str(0x35, '\0');
    const auto  result = LZ4_decompress_safe(compressed.data(), str.data(), compressed.size(), 0x35);
    str.resize(result);
    for (unsigned char c : str) {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)c << "";
    }
    cout << endl;

    for (int m = str.size() - 1; m >= 1; --m)
        str[m] ^= str[m - 1];

    uint8_t s[256];
    uint8_t key[9] = { 0x72, 0xff, 0x98, 0x96, 0x99, 0x06, 0xe9, 0xb7, 0x22 };
    rc4_init(s, key, 9);
    rc4_crypt(s, str);
}