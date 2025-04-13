// [深入Python C API：掌握常用函数与实战技巧](https://mp.weixin.qq.com/s/KdCKBi9LVUgB7jSWwt-yyA)
// 配置环境:  c_cpp_tutorial\Windows_VisualStudio.md#使用Python.h编译程序

#include <Python.h>

int main() {
    Py_Initialize();  // 初始化解释器
    // 执行Python相关操作
    PyRun_SimpleString("print('Hello from C!')");  // 输出：Hello from C!
    Py_Finalize();    // 清理解释器资源
    return 0;
}