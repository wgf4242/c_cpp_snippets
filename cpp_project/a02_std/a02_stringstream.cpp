// ���Ա��� g++ -g -o myprogram a02_stringstream.cpp
#include <iostream>
#include <sstream> // ���� sstream ͷ�ļ���ʹ�� stringstream

int main() {
    std::stringstream stream; // ����һ���ַ���������
    int v6;

    // ֱ�Ӵ� cin ��ȡ��д�뵽 stream
    for (int i = 0; i <= 4; ++i) {
        std::cin >> v6;
        stream << v6 << " "; // ����ȡ������д�����������һ���ո�
    }

    // ��ӡ���յ��ַ���������
    std::cout << "�����ַ���������: " << stream.str() << std::endl;

    return 0;
}