#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <deque>

using namespace std;

int add(int a, int b) {
    return a + b;
}

void printVector(vector<int> vi) {
    // for (vector<int>::iterator it = vi.begin(); it != vi.end(); it++) { cout << *it << " "; }

    // for (auto x: vi)
    //     cout << x << " ";

    for (auto x: vi)
        cout << x << " ";
    cout << endl;
}

TEST(VectorTests, InitVector) {
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(0);

    vector<int> original = {1, 2, 3, 4};

    printVector(v);
    printVector(original);

    // EXPECT_EQ(add(2, 3), 5);
}

TEST(VectorTests, VectorMethods) {
    vector<int> v = {5, 6, 3, 4};
    int i = 2;

    // 基本操作
    v.size();             // 当前元素数量
    v.empty();            // 是否为空
    // v.clear();            // 清空所有元素
    v.push_back(19);       // 添加元素到末尾（append）
    v.pop_back();         // 删除末尾元素
    v.back();             // 获取最后一个元素
    v.front();            // 获取第一个元素
    v[i];                 // 访问第 i 个元素
    v.at(i);              // 安全访问第 i 个元素（带越界检查）
    v.reserve(5);     // 提高性能, 申请至少 n 个元素空间
}

TEST(VectorTests, VectorUpdates) {
    vector<int> v = {5, 6, 3, 4};
    int i = 2, x = 2, j = 3;

    //修改操作
    v.insert(v.begin() + i, x);             // 在第 i 位插入元素
    v.erase(v.begin() + i);                 // 删除第 i 位的元素
    v.erase(v.begin() + i, v.begin() + j);  // 删除 i 到 j-1 的元素
    reverse(v.begin(), v.end());       // 翻转
    printVector(v);
    sort(v.begin(), v.end());          // 升序排序
    sort(v.rbegin(), v.rend());        // 降序排序
    printVector(v);
}

TEST(VectorTests, findCountUnique) {
    vector<int> v = {5, 3, 6, 4, 3};
    int x = 3;

    auto it = find(v.begin(), v.end(), x);
    if (it != v.end()) {
        cout << "元素 " << x << " 找到了，位置索引为: " << distance(v.begin(), it) << endl;
    } else {
        cout << "元素 " << x << " 未找到。" << endl;
    }

    int cnt = count(v.begin(), v.end(), x);      // 统计 x 出现次数
    cout << "元素 " << x << " 出现的次数为: " << cnt << endl;

    // 3. 去重（需先排序）
    sort(v.begin(), v.end()); // 去重前需要排序
    v.erase(unique(v.begin(), v.end()), v.end());

    printVector(v);
}

TEST(VectorTests, CopyVectors) {
    // 方式 1：直接赋值（推荐，最简单）
    vector<int> original = {1, 2, 3, 4};
    vector<int> v1 = original;

    // 🧱 方式 2：构造函数复制
    vector<int> copy_item(original); // 和方式1等效
    copy_item.pop_back();
    printVector(copy_item);

    // 🧱 方式 3：复制部分（区间复制）
    vector<int> partial_copy_item(original.begin(), original.begin() + 2);
    printVector(partial_copy_item);

    std::pop_heap(original.begin(), original.end());
    printVector(original);
}

TEST(VectorTests, OtherMethods) {
    // 其他有用的 STL 函数（与 vector 配合）
    // accumulate(v.begin(), v.end(), 0);   // 所有元素求和
    // min_element(v.begin(), v.end());    // 最小值的迭代器
    // max_element(v.begin(), v.end());    // 最大值的迭代器
    // lower_bound(v.begin(), v.end(), x); // 返回 >=x 的第一个位置（需排序）
    // upper_bound(v.begin(), v.end(), x); // 返回 >x 的第一个位置（需排序）
}

TEST(VectorTests, DequeAdvanced) {
    deque<int> dq = {1, 2, 3, 4};
    dq.pop_front();  // 高效删除第一个元素
    dq.push_front(5);

    vector<int> vec(dq.begin(), dq.end());
    printVector(vec);
}
