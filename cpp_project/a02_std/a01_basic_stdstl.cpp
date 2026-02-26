#include <iostream>
#include <vector>    // 动态数组
#include <map>       // 键值对映射
#include <algorithm> // 排序算法
#include <string>

using namespace std;

int main() {
    // ---- 1. Vector使用 ----
    // 想象我们要记录一组学生的成绩
    vector<int> scores = { 85, 92, 78, 99, 88 };

    cout << "---- Vector使用 ----" << endl;
    cout << "原始成绩列表: ";
    for (int s : scores) cout << s << " ";
    cout << endl;

    // ---- 2. Sort算法使用 ----
    // 快速给成绩排个序
    sort(scores.begin(), scores.end());

    cout << "---- Sort算法使用 ----" << endl;
    cout << "排序后的成绩: ";
    for (int s : scores) cout << s << " ";
    cout << endl;

    // ---- 3. Map使用 ----
    // 将名字和最高分关联起来
    map<string, int> topStudents;
    topStudents["张三"] = scores.back(); // 取排序后的最后一个（最高分）
    topStudents["李四"] = 92;

    cout << "---- Map使用 ----" << endl;
    cout << "张三的最高分记录为: " << topStudents["张三"] << " 分" << endl;

    return 0;
}