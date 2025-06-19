# Makefile for TCP Client

CC = gcc
CFLAGS = -Wall -Wextra -O2 -s
LDFLAGS = -lws2_32
CONSOLE_TARGET = client_console.exe
BACKGROUND_TARGET = client.exe
SOURCE = client.c

# 默认目标 - 编译两个版本
all: console background

# 控制台版本
console: $(CONSOLE_TARGET)

$(CONSOLE_TARGET): $(SOURCE)
	@echo 正在编译控制台版本...
	$(CC) $(CFLAGS) -DCONSOLE_MODE -o $(CONSOLE_TARGET) $(SOURCE) $(LDFLAGS)
	@echo 编译完成！生成了 $(CONSOLE_TARGET)

# 后台版本
background: $(BACKGROUND_TARGET)

$(BACKGROUND_TARGET): $(SOURCE)
	@echo 正在编译后台版本...
	$(CC) $(CFLAGS) -mwindows -o $(BACKGROUND_TARGET) $(SOURCE) $(LDFLAGS)
	@echo 编译完成！生成了 $(BACKGROUND_TARGET)

# 清理目标
clean:
	@echo 清理编译文件...
	@if exist $(CONSOLE_TARGET) del $(CONSOLE_TARGET)
	@if exist $(BACKGROUND_TARGET) del $(BACKGROUND_TARGET)
	@echo 清理完成！

# 运行控制台版本
run-console: $(CONSOLE_TARGET)
	@echo 运行控制台版本...
	.\$(CONSOLE_TARGET)

# 运行后台版本
run-background: $(BACKGROUND_TARGET)
	@echo 运行后台版本...
	.\$(BACKGROUND_TARGET)

# 帮助信息
help:
	@echo 可用的目标：
	@echo   all           - 编译两个版本（默认）
	@echo   console       - 只编译控制台版本
	@echo   background    - 只编译后台版本
	@echo   clean         - 清理编译文件
	@echo   run-console   - 编译并运行控制台版本
	@echo   run-background- 编译并运行后台版本
	@echo   help          - 显示此帮助信息
	@echo.
	@echo 使用方法：
	@echo   控制台版本：client_console.exe -i IP -p 端口
	@echo   后台版本：  client.exe -i IP -p 端口

.PHONY: all console background clean run-console run-background help