
#include <string.h>
#include "stdio.h"

void test_debug();

int main(int argc, char *argv[], char **env) {
    test_debug();
    return 0;
}

void test_debug() {
#ifdef DEBUG
    // CMakeLists.txt 添加 add_compile_definitions(DEBUG=1)
        printf("正在使用 Debug 模式编译程序...\n");
#else
    printf("正在使用 Release 模式编译程序...\n");
#endif
}
