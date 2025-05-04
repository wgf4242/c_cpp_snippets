#ifndef _TESTLIB_H
#define _TESTLIB_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <link.h>
#include <elf.h>

// 必须完整定义 audit_ifaces 结构
struct audit_ifaces {
    uint64_t (*symbind64)(Elf64_Sym*, void*, void*, void*, void*, char*);
};

extern struct audit_ifaces dl_audit;  // 声明全局变量

// Function pointer type for foo
typedef void (*foo_t)(void);

// 函数声明
void foo_1(void);
void foo_2(void);
void foo(void);
foo_t foo_resolver(void);
void hook_aes_func(char *key, int length, char *enc_key);
uint64_t install_hook(Elf64_Sym *a1, void *a2, void *a3, void *a4, void *a5, char *sym_name);
void *findLdBase(void);
void *findSymAddr(void *addr, const char *symbol, int mode);
void setAuditPtr(struct link_map *r_map);
int doBackdoor(void);

#endif /* _TESTLIB_H */