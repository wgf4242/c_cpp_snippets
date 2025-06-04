# Makefile for Linux Hook Examples
# 根据文章 https://mp.weixin.qq.com/s/vEFLiGJl21eTxXRhbwA6zA 实现的各种Hook技术

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -ldl
SHARED_FLAGS = -fPIC -shared

# 目标文件
TARGETS = hook_example function_pointer_hook gcc_attribute_hook demo_program test_program
LIBRARIES = libmyhook.so libadvancedhook.so

# 默认目标
all: $(TARGETS) $(LIBRARIES)

# 编译基本的hook示例
hook_example: hook_example.c
	$(CC) $(CFLAGS) -o $@ $<
hook_example1: hook_example1.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译函数指针hook示例
function_pointer_hook: function_pointer_hook.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译GCC属性hook示例
gcc_attribute_hook: gcc_attribute_hook.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译演示程序
demo_program: demo_program.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译测试程序
test_program: test_program.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译LD_PRELOAD hook库
libmyhook.so: ld_preload_hook.c
	$(CC) $(SHARED_FLAGS) -o $@ $< $(LDFLAGS)

# 编译高级hook库
libadvancedhook.so: advanced_hook.c
	$(CC) $(SHARED_FLAGS) -o $@ $< $(LDFLAGS)

# 清理目标
clean:
	rm -f $(TARGETS) $(LIBRARIES) *.o

# 测试目标
test: all
	@echo "=== 测试基本hook示例 ==="
	./hook_example
	@echo "\n=== 测试函数指针hook ==="
	./function_pointer_hook
	@echo "\n=== 测试GCC属性hook ==="
	./gcc_attribute_hook
	@echo "\n=== 测试LD_PRELOAD hook (需要Linux环境) ==="
	@echo "运行命令: LD_PRELOAD=./libmyhook.so ./test_program test"
	@echo "\n=== 测试高级hook库 (需要Linux环境) ==="
	@echo "运行命令: LD_PRELOAD=./libadvancedhook.so ./demo_program"

# 安装目标
install: all
	@echo "将库文件复制到系统目录需要root权限"
	@echo "sudo cp $(LIBRARIES) /usr/local/lib/"
	@echo "sudo ldconfig"

# 帮助信息
help:
	@echo "可用的make目标:"
	@echo "  all        - 编译所有程序和库"
	@echo "  clean      - 清理编译文件"
	@echo "  test       - 运行测试"
	@echo "  install    - 安装库文件"
	@echo "  help       - 显示此帮助信息"
	@echo ""
	@echo "Hook技术说明:"
	@echo "  1. hook_example - 基本钩子函数实现"
	@echo "  2. function_pointer_hook - 函数指针封装"
	@echo "  3. libmyhook.so - LD_PRELOAD动态链接库劫持"
	@echo "  4. gcc_attribute_hook - GCC特定语法hook"
	@echo "  5. libadvancedhook.so - 高级hook库(多函数)"
	@echo ""
	@echo "使用示例:"
	@echo "  LD_PRELOAD=./libmyhook.so ./test_program test"
	@echo "  LD_PRELOAD=./libadvancedhook.so ./demo_program"

.PHONY: all clean test install help