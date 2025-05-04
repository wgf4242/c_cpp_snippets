#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // 定义栈的最大容量

typedef struct {
    int arr[MAX_SIZE]; // 用于存储栈元素的数组
    int top;           // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 检查栈是否已满
int isFull(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// 元素入栈
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Error: Stack is full\n");
        return;
    }
    s->arr[++(s->top)] = value;
    printf("Pushed %d to stack\n", value);
}

// 元素出栈
int pop(Stack *s) {
    if (s->top == -1) {
        printf("Error: Stack is empty\n");
        return -1; // 或者你可以选择抛出一个异常，或者定义一个特殊的错误码
    }
    int value = s->arr[s->top--];
    printf("Popped %d from stack\n", value);
    return value;
}


int main() {
    Stack myStack;
    initStack(&myStack);

    // 使用宏定义的方式进行压栈操作
    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);

    // 使用pop方法进行出栈操作
    int v1 = pop(&myStack);
    int v2 =  pop(&myStack);
    int v3 =  pop(&myStack);
    int v4 =  pop(&myStack); // 测试空栈情况

    return 0;
}
