// 大对象 大数问题
#include <gtest/gtest.h>
#include <windows.h>  // For GetFinalPathNameByHandle
#include <cstdio>
#include <io.h>  // for _get_osfhandle


TEST(Performence, Example) {
    // 大对象的传递会成为性能问题。以下是一个简单示例
    class BigObject {
    private:
        int data[10000]; // 假设这是一个很大的数据结构
    public:
        BigObject() {
            for (int i = 0; i < 10000; i++) {
                data[i] = i;
            }
        }
    };

    // 低效的传递方式 - 值传递会导致整个对象被复制
    void processObject(BigObject obj) {
        // 处理对象
    }

    // 更高效的传递方式
    void processObjectRef(const BigObject &obj) {
        // 处理对象
    }
}

TEST(Performence, CopyDeepCopy) { // 深拷贝与浅拷贝示例
    // 深拷贝与浅拷贝示例
    class StringClass {
    private:
        char *data;
        size_t length;

    public:
        // 构造函数
        StringClass(const char *str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        }

        // 析构函数
        ~StringClass() {
            delete[] data;
        }

        // 浅拷贝(默认拷贝构造函数) - 会导致问题
        // StringClass(const StringClass& other) = default;

        // 深拷贝(正确的拷贝构造函数)
        StringClass(const StringClass &other) {
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }

        // 拷贝赋值运算符
        StringClass &operator=(const StringClass &other) {
            if (this != &other) {
                delete[] data; // 释放原有资源
                length = other.length;
                data = new char[length + 1];
                strcpy(data, other.data);
            }
            return *this;
        }
    };

}


TEST(Performence, MoveConstructor) {
    // 移动语义示例
    class Resource {
    private:
        int *data;
        size_t size;

    public:
        // 构造函数
        Resource(size_t sz) : size(sz) {
            data = new int[size];
        }

        // 析构函数
        ~Resource() {
            delete[] data;
        }

        // 拷贝构造函数
        Resource(const Resource &other) : size(other.size) {
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "拷贝构造" << std::endl;
        }

        // 移动构造函数
        Resource(Resource &&other) noexcept: data(other.data), size(other.size) {
            other.data = nullptr; // 防止源对象析构时释放内存
            other.size = 0;
            std::cout << "移动构造" << std::endl;
        }

        // 移动赋值运算符
        Resource &operator=(Resource &&other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
            }
            std::cout << "移动赋值" << std::endl;
            return *this;
        }
    };

    // 使用示例
    void useResource() {
        Resource r1(1000);

        // 拷贝构造
        Resource r2 = r1;

        // 移动构造
        Resource r3 = std::move(r1); // r1不再拥有资源
    }
}

TEST(Performence, RVO) {
    // 返回值优化示例
    class HeavyObject {
    private:
        int data[10000];
    public:
        HeavyObject() {
            std::cout << "构造函数" << std::endl;
        }

        HeavyObject(const HeavyObject &) {
            std::cout << "拷贝构造函数" << std::endl;
        }

        ~HeavyObject() {
            std::cout << "析构函数" << std::endl;
        }
    };

    // 编译器可能会应用RVO优化，避免不必要的拷贝
    HeavyObject createObject() {
        HeavyObject obj; // 只会调用一次构造函数
        return obj;      // 不会调用拷贝构造函数
    }

    // 使用示例
    void testRVO() {
        HeavyObject obj = createObject(); // 可能只会调用一次构造函数
    }
}


TEST(Performence, Cow) {
    // 写时复制(COW)策略示例
#include <memory>
#include <iostream>

    class COWString {
    private:
        struct StringData {
            char *data;
            size_t length;
            size_t ref_count;

            StringData(const char *str) : ref_count(1) {
                length = strlen(str);
                data = new char[length + 1];
                strcpy(data, str);
            }

            ~StringData() {
                delete[] data;
            }
        };

        std::shared_ptr<StringData> str_data;

    public:
        // 构造函数
        COWString(const char *str) : str_data(new StringData(str)) {}

        // 拷贝构造函数 - 只增加引用计数，不复制数据
        COWString(const COWString &other) : str_data(other.str_data) {}

        // 获取字符 - 只读操作
        char operator[](size_t index) const {
            return str_data->data[index];
        }

        // 修改字符 - 写操作，需要复制
        char &operator[](size_t index) {
            // 如果有多个对象共享数据，则需要复制
            if (str_data.use_count() > 1) {
                // 创建新的数据副本
                StringData *new_data = new StringData(str_data->data);
                str_data.reset(new_data);
            }
            return str_data->data[index];
        }
    };

    // 使用示例
    void testCOW() {
        COWString s1("Hello");
        COWString s2 = s1; // 不会复制数据，只增加引用计数

        char c = s1[0]; // 只读操作，不会复制

        s2[0] = 'h'; // 写操作，会触发复制
    }
}

TEST(Performence, std_swap) {
    // std::swap优化示例
    class SwapOptimized {
    private:
        int* data;
        size_t size;

    public:
        SwapOptimized(size_t sz) : size(sz) {
            data = new int[size];
        }

        ~SwapOptimized() {
            delete[] data;
        }

        // 移动构造函数
        SwapOptimized(SwapOptimized&& other) noexcept
                : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
        }

        // 移动赋值运算符
        SwapOptimized& operator=(SwapOptimized&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
            }
            return *this;
        }

        // 自定义swap函数
        friend void swap(SwapOptimized& first, SwapOptimized& second) noexcept {
            // 使用std::swap交换成员
            std::swap(first.data, second.data);
            std::swap(first.size, second.size);
        }
    };
}
