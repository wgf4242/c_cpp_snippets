#include <iostream>
#include <string>

void cstr_test();

void str_construct();

int cstr_find();

void printf_format() {
    printf("%02x", 2);
}

using namespace std;


int main() {
    // str_construct();
    // cstr_test();
    cstr_find();
    return 0;
}

int cstr_find() {
    string str = "select * from a ";
    string arr[]{"select1", "and"};
    if (str.find(arr[0].c_str())) {
        return 0;
    } else {
        return -1;
    }

}

void cstr_test() {
    const char *ptr;
    string s = "12345";
    ptr = s.c_str();

    cout << "s改变前ptr为：" << ptr << endl;
    s = "66666";
    cout << "s改变后ptr为：" << ptr << endl;
}

void str_construct() {
    std::string str("Sairamkrishna Mammahe");
    // for (int i=0; i<str.length(); ++i) {
    for (char i: str) {
        std::cout << i;
    }
    std::cout << std::endl;
    std::cout << std::hex << 0x31; // print as hex
}
