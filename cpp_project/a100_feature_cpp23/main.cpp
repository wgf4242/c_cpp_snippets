#include <print>

int main() {
  std::print("Hello, {}!\n", "World");    // 输出: Hello, World!
  std::print("The answer is: {}\n", 42);  // 输出: The answer is: 42
  return 0;
}