// 省赛题目 luoing 
#include <array>
#include <cstdint>
#include <iostream>
#include <random>

// 调试器检测
constexpr bool kDebuggerFound = true;

int main() {
    std::mt19937 mt19937(kDebuggerFound ? 0x7D1 : 0x44C);

    std::array<uint8_t, 38> ctf_flag = {
            0xC2, 0x6C, 0xFC, 0xB3, 0xA7, 0x8E, 0xF5, 0x83, 0x81, 0xCB,
            0xBF, 0xD5, 0xC2, 0xCE, 0x83, 0xBD, 0xE6, 0x6A, 0xA5, 0xA8,
            0x44, 0xF5, 0x45, 0x59, 0x50, 0xD8, 0x03, 0x98, 0xF7, 0x74,
            0x87, 0xAC, 0xC5, 0x3E, 0x38, 0x2F, 0x07, 0x68};

    for (auto &v : ctf_flag) {
        v ^= mt19937();
    }

    std::cout << "flag: ";
    for (auto &v : ctf_flag) {
        std::cout << (char)(v);
    }
    std::cout << std::endl;
}