// msvc ÷–±‡“Î
#define _CRT_SECURE_NO_WARNINGS
//print
#include <cstdio>
#include <filesystem>
#include <print>

int main()
{
    std::print("{2} {1}{0}!\n", 23, "C++", "Hello");  // overload (1) // Hello C++23!

    const auto tmp{ std::filesystem::temp_directory_path() / "test.txt" };
    if (std::FILE * stream{ std::fopen(tmp.string().c_str(), "w") })
        //if (std::FILE * stream{ std::fopen(tmp.c_str(), "w") })
    {
        std::print(stream, "File: {}", tmp.string()); // overload (2) // File: C:\Users\IBM\AppData\Local\Temp\test.txt
        std::fclose(stream);
    }

    std::vector<int> vec = { 11, 32, 77 };
    std::print("vec elements: {}\n", vec); // vec elements: [11, 32, 77]

    std::println("Hello!");  // Hello!

    double val = 3.18;
    std::string test{ "Hello" };
    std::println("{} - {} !", test, val); // Hello - 3.18 !

    return 0;
}