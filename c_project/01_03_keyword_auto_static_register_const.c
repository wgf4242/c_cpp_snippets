// https://mp.weixin.qq.com/s/jf7ZtjJeOcs7_Yyj2HGqSA
# include <stdio.h>

// 1. 关键字auto通常用于声明局部变量，它告诉编译器将变量存储在自动存储类中。这意味着变量的生命周期与其作用域相同，即在进入和离开作用域时自动分配和释放内存
void someFunction() {
    auto int x = 10;  // auto声明的变量会自动分配内存
    // ...
}

// 2. static关键字有两个主要的用法。首先，可以用于限制变量的作用域。当一个变量被声明为静态时，其作用域仅限于当前代码块，其他代码块无法访问该变量。例如：
// 每次调用someFunction()函数时，count都会保留上一次调用后的值。其次，static关键字还可以用于限制函数的作用域，使其仅在当前源文件可见。
void someFunction_static() {
    static int count = 0;  // 静态变量只在当前函数作用域中可见
    count++;
    printf("Count: %d\n", count);
}

// 3. const关键字用于声明一个常量，其值在程序执行期间不可更改。常量在声明时必须进行初始化。 const关键字通常用于声明不可更改的数组、指针和函数参数。
const int MAX_VALUE = 100;  // 定义一个常量MAX_VALUE，并初始化为100

void someFunctionConst() {
    const int VALUE = 10;  // 常量VALUE只在当前函数作用域中可见
    // VALUE = 20; // 编译错误，常量不可更改
}

// 4. volatile关键字用于告诉编译器某个变量的值可能在程序执行期间被更改，该变量的访问不应被优化。这在多线程、并发编程以及与硬件交互的程序中很有用。例如：
volatile int flag = 0;  // 告诉编译器变量flag的值可能会被更改

void someFunctionVolatile() {
    while (flag == 0) {
        // 在循环中检测flag值的变化
    }
}

// extern关键字用于声明一个变量或函数是在其他源文件中定义的。它用于在当前源文件中引用其他文件中定义的全局变量或函数。例如：
extern int globalVariable;  // 引用其他源文件中定义的全局变量
extern void someFunctionExtern();  // 引用其他源文件中定义的函数

int main(void)
{
    // 5. register关键字用于给编译器建议，告诉它将变量存储在寄存器中，以便提高访问速度。然而，现代编译器通常能够自动优化变量的存储方式，因此register关键字的使用并不常见。例如：
    register int x;  // 将变量x存储在寄存器中

    return 0;
}