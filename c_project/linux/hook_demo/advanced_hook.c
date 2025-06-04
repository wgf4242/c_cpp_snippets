//gcc -fPIC -shared -o libadvancedhook.so advanced_hook.c -ldl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <unistd.h>

// Hook malloc函数
typedef void* (*MALLOC)(size_t);
static MALLOC old_malloc = NULL;

void* malloc(size_t size)
{
    if (!old_malloc) {
        old_malloc = (MALLOC)dlsym(RTLD_NEXT, "malloc");
    }
    
    void *ptr = old_malloc(size);
    // 使用write系统调用避免printf递归
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "[HOOK] malloc(%zu) = %p\n", size, ptr);
    write(STDERR_FILENO, buffer, len);
    return ptr;
}

// Hook free函数
typedef void (*FREE)(void*);
static FREE old_free = NULL;

void free(void *ptr)
{
    if (!old_free) {
        old_free = (FREE)dlsym(RTLD_NEXT, "free");
    }
    
    // 使用write系统调用避免printf递归
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "[HOOK] free(%p)\n", ptr);
    write(STDERR_FILENO, buffer, len);
    old_free(ptr);
}

// Hook printf函数 - 简化版本避免复杂的递归问题
typedef int (*PRINTF)(const char*, ...);
static PRINTF old_printf = NULL;
static __thread int in_printf = 0;  // 使用线程局部存储

int printf(const char *format, ...)
{
    // 防止递归调用
    if (in_printf) {
        // 如果已经在printf hook中，直接调用原始函数
        if (!old_printf) {
            old_printf = (PRINTF)dlsym(RTLD_NEXT, "printf");
        }
        va_list args;
        va_start(args, format);
        int result = old_printf ? old_printf(format, args) : vprintf(format, args);
        va_end(args);
        return result;
    }
    
    if (!old_printf) {
        old_printf = (PRINTF)dlsym(RTLD_NEXT, "printf");
    }
    
    in_printf = 1;
    
    // 先输出前缀
    if (old_printf) {
        old_printf("[HOOKED] ");
    }
    
    // 然后输出原始内容
    va_list args;
    va_start(args, format);
    int result = old_printf ? old_printf(format, args) : vprintf(format, args);
    va_end(args);
    
    in_printf = 0;
    
    return result;
}

// 库初始化函数
__attribute__((constructor))
static void init_hook(void)
{
    // 使用write避免printf递归
    const char *msg = "Advanced hook library loaded\n";
    write(STDERR_FILENO, msg, strlen(msg));
}

// 库清理函数
__attribute__((destructor))
static void cleanup_hook(void)
{
    // 使用write避免printf递归
    const char *msg = "Advanced hook library unloaded\n";
    write(STDERR_FILENO, msg, strlen(msg));
}