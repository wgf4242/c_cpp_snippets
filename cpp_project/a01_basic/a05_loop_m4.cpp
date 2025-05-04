// .类静态变量
//         创建一个Test数组，元素为100个，静态变量每次累加。

#include <iostream>
using namespace std;

class Test {
    static int i;

public:
    Test() { cout << ++i << endl; }
};
int Test::i;
int main() {
    Test a[100];
    return 0;
}