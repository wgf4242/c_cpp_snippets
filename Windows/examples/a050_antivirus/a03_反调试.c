#include <windows.h>
#include <stdio.h>

void checkDebugger() {
    if (IsDebuggerPresent()) {
        ExitProcess(1);
}

int main() {
    checkDebugger();
    return 0;
}