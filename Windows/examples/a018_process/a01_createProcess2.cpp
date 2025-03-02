# include <stdio.h>
# include <Windows.h>

void StartCalculator() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// 初始化结构体
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	wchar_t commandLine[] = L"calc.exe";

	// 使用CreateProcess启动计算器进程
	if (CreateProcess(
		NULL,           // 应用程序名称（NULL表示使用命令行）
		commandLine,     // 命令行参数，这里直接运行calc.exe
		NULL,           // 进程安全属性
		NULL,           // 线程安全属性
		FALSE,          // 不继承句柄
		0,              // 创建标志
		NULL,           // 环境块
		NULL,           // 当前目录
		&si,            // 启动信息
		&pi             // 进程信息
	)) {
		// 创建成功后关闭句柄，避免资源泄漏
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		// 如果创建失败，输出错误信息
		std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 入口函数
int main()
{
	StartCalculator();
	return 0;
}