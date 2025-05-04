#include <iostream>
#include <Windows.h>
#include <string>
// 实现含有中文字符的字符串逆转，如：“我是小萌新”转换成“新萌小是我”

using namespace std;

void ni_zhuan_str(string &str, int len) {
    int lenth = len;

    for (int i = 0; i < lenth / 2; i += 2, len -= 2) {
        int ret = str[i];
        str[i] = str[len - 2];
        str[len - 2] = ret;

        ret = str[i + 1];
        str[i + 1] = str[len - 1];
        str[len - 1] = ret;
    }
}

int main(void) {
    string str;

    cout << "请输入中文字符串：";
    cin >> str;

    int len = str.length();
    ni_zhuan_str(str, len);

    cout << "逆转后：" << str << endl;

    system("pause");
    return 0;
}

