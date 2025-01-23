// gcc a4.c -o a4.out
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>

int main() {
    pid_t v4 = fork();

    if (v4) {
        // 父进程
        wait(NULL); // 等待子进程暂停
        printf("Child process paused. Attach IDA to PID: %d\n", v4);
        getchar(); // 等待用户输入

        // 继续执行子进程
        ptrace(PTRACE_CONT, v4, NULL, NULL);
        wait(NULL); // 等待子进程结束
    } else {
        // 子进程
        ptrace(PTRACE_TRACEME, 0, NULL, NULL); // 标记为被调试状态
        raise(SIGSTOP); // 暂停进程，等待父进程或调试器附加
        execl("./a2.out", "a2.out", NULL); // 执行目标程序
    }

    return 0;
}