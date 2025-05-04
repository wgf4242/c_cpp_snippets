#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>

#define SYS_CALL_myread 12345
#define SYS_CALL_mywrite 67890

void mywrite(char *str) {
    syscall(SYS_CUSTOM_write, str, 1, strlen(str));
}
// 反调试
void tracer(pid_t child_pid) {
    int status;
    waitpid(child_pid, &status, 0);
    if (!WIFSTOPPED(status)) {
        printf("Incorrect state.\n");
        return;
    }
    ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_EXITKILL);
    struct user_regs_struct regs;
    while (WIFSTOPPED(status)) {
        ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
        waitpid(child_pid, &status, 0);
        ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
        if (regs.orig_rax == SYS_CUSTOM_write) {
            //printf("CUSTOM_write found, patched.\n");
            regs.orig_rax = SYS_write;
            //swap arg1 & arg2
            unsigned long long int orig_rdi = regs.rdi;
            regs.rdi = regs.rsi;
            regs.rsi = orig_rdi;

            ptrace(PTRACE_SETREGS, child_pid, 0, &regs);
        }
        ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
        waitpid(child_pid, &status, 0);
    }
}
__attribute((constructor(101))) void before_main() {
    // if (ptrace(PTRACE_TRACEME, 0,0,0) == -1) {
    //     return 1
    // }
    pid_t child_pid = fork();
    if (child_pid < 0) {
        exit(1);
    }
    if (child_pid == 0) {
        if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
            return 1;
        }
        // raise(SIGCONT); //向自身发送SIGCONT信号, 表示继续执行
    } else {
        tracer(child_pid);
    }
}
__attribute((constructor(102))) void before_main2() {
    int a = 86, b = 17, c = 643;
    for (int i = 0; i < 16; ++i) {
        a += i;
    }
}

int main(int argc, char const *argv[]) {
    puts("Round 6 ");
    return 0;
}