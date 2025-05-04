#include <Python.h>

int main() {
    Py_Initialize();  // 初始化解释器
    // 执行Python相关操作
    PyRun_SimpleString("print('Hello from C!')");  // 输出：Hello from C!
    Py_Finalize();    // 清理解释器资源
    return 0;
}

PyObject* func1() {
    // 创建字典
    PyObject* dict = PyDict_New();
    if (dict == NULL) {
        PyErr_Print();
        return 1;
    }

    // 定义 Python 函数
    const char* python_code = "def my_function(x): return x";
    PyObject* result = PyRun_String(python_code, Py_file_input, dict, dict);
    if (result == NULL) {
        PyErr_Print();
        Py_DECREF(dict);
        Py_Finalize();
        return 1;
    }
    Py_DECREF(result); // result 是 None

    // 从字典中获取函数对象
    PyObject* func = PyDict_GetItemString(dict, "my_function");
    if (func == NULL) {
        PyErr_Print();
        Py_DECREF(dict);
        Py_Finalize();
        return 1;
    }
    Py_INCREF(func);
    return func;
}

int testFunction() {

    // 三、返回值构建：从C到Python的转换
    // 1. Py_BuildValue()‌  功能‌：将C变量组合成Python对象。
    PyObject* result = Py_BuildValue("(iis)", 42, 3.14, "hello");

    // 五、引用计数与内存管理
    // Python使用引用计数管理内存，以下操作至关重要：

    // 1. Py_INCREF() 和 Py_DECREF()‌
    // 规则‌：
    // 任何新创建的Python对象（如通过Py_BuildValue）的引用计数为1。
    // 在传递对象所有权时需手动增减引用。

    PyObject* obj = PyList_New(0);  // 引用计数=1
    Py_INCREF(obj);  // 引用计数=2
    Py_DECREF(obj);  // 引用计数=1
    Py_DECREF(obj);  // 引用计数=0，对象被销毁

    // 2. Py_XDECREF()‌
    // 安全释放‌：即使对象为NULL也不会崩溃。
    // PyObject * possibly_null = ...;
    // Py_XDECREF(possibly_null);  // 安全操作
    
    // 六、异常处理 1. 抛出异常
    int error_occurred = 1;
    if (error_occurred) {
        PyErr_SetString(PyExc_ValueError, "Invalid value");
        return NULL;  // 函数返回NULL表示异常已设置
    }



    // 2. 检查异常
    PyObject* func = func1();
    PyObject* result = PyObject_CallFunction(func, "i", 42);
    if (!result) {
        if (PyErr_Occurred()) {
            PyErr_Print();  // 打印错误信息到stderr
        }
        // 处理错误
    }
    return 0;
}

// 1. PyArg_ParseTuple()
// 功能‌：解析Python函数的位置参数（* args）。‌
// 格式字符串‌：
// i：整型
// f：浮点型
// s：字符串（const char* ）
// O：任意Python对象（PyObject* ）

static PyObject* add(PyObject* self, PyObject* args) {
    int a, b;
    // 解析两个整数参数
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;// 解析失败时返回NULL，触发Python异常
    }
    returnPyLong_FromLong(a + b);
}

// 2. PyArg_ParseTupleAndKeywords()‌
// 功能‌：解析位置参数和关键字参数（ * args, ** kwargs）。

static PyObject* greet(PyObject* self, PyObject* args, PyObject* kwargs) {
    static char* keywords[] = { "name","age",NULL };
    const char* name;
    int age;

    // 格式字符串"si"表示字符串+整型
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "si", keywords, &name, &age)) {
        return NULL;
    }
    printf("Name: %s, Age: %d\n", name, age);
    Py_RETURN_NONE;// 返回Python的None
}


// 四、模块与函数定义
// 1. 定义模块方法表
static PyMethodDef MyMethods[] = {
    {"add", add, METH_VARARGS, "Add two integers."},
    {"greet", greet, METH_VARARGS | METH_KEYWORDS, "Print a greeting."},
    {NULL, NULL, 0, NULL}  // 结束标记
};

// 2.模块初始化
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "mymodule",   // 模块名
    NULL,         // 模块文档
    -1,           // 模块状态（-1表示全局状态）
    MyMethods     // 方法表
};

PyMODINIT_FUNC PyInit_mymodule(void) {
    returnPyModule_Create(&mymodule);
}




// 七、实战案例：实现矩阵乘法
static PyObject* matrix_multiply(PyObject * self, PyObject * args) {
    PyObject* matrix1, * matrix2;
    if (!PyArg_ParseTuple(args, "OO", &matrix1, &matrix2)) return NULL;

    // 验证输入为二维列表
    if (!PyList_Check(matrix1) || !PyList_Check(matrix2)) {
        PyErr_SetString(PyExc_TypeError, "Input must be a list");
        return NULL;
    }

    // 矩阵乘法逻辑（此处简化为示例）
    // ... 实际实现矩阵乘法 ...

    // 返回结果矩阵
    PyObject* result = PyList_New(0);
    // 填充计算结果...
    return result;
}

// 注册方法并初始化模块（略）

