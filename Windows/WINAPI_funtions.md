

# Funcitons

## CreateProcess

```
BOOL WINAPI CreateProcess(
  _In_opt_ LPCSTR lpApplicationName,
  _Inout_opt_ LPSTR lpCommandLine,
  _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_ BOOL bInheritHandles,
  _In_ DWORD dwCreationFlags,
  _In_opt_ LPVOID lpEnvironment,
  _In_opt_ LPCSTR lpCurrentDirectory,
  _In_ LPSTARTUPINFO lpStartupInfo,
  _Out_ LPPROCESS_INFORMATION lpProcessInformation
);
```







## WinHTTP通信机制详解

恶意软件使用WinHTTP API进行网络通信。WinHTTP是Windows提供的高级HTTP客户端接口，专门用于服务和后台应用程序。

**典型的WinHTTP通信流程**

```
1. WinHttpOpen()
   - 初始化HTTP会话
   - 设置User-Agent字符串
   - 返回会话句柄

2. WinHttpConnect()
   - 连接到目标服务器（5.39.218.152）
   - 指定端口号（默认80或443）
   - 返回连接句柄

3. WinHttpOpenRequest()
   - 创建HTTP请求对象
   - 指定HTTP方法（POST）
   - 指定请求路径
   - 返回请求句柄

4. WinHttpSendRequest()
   - 发送HTTP请求头
   - 发送请求体数据
   - 等待服务器响应

5. WinHttpReceiveResponse()
   - 接收服务器的HTTP响应
   - 解析响应头

6. WinHttpReadData()
   - 读取响应体内容
   - 可能包含攻击者的指令

7. WinHttpCloseHandle()
   - 关闭所有句柄
   - 释放资源
```

**为什么选择WinHTTP而不是WinINet**

WinHTTP相比WinINet有以下优势：

- 更适合服务和后台应用程序
- 不受Internet Explorer设置影响
- 更好的代理支持和配置灵活性
- 更稳定的服务器端通信
- 支持异步操作

这些特性使得WinHTTP成为恶意软件开发者的首选，特别是针对工业控制系统这类需要稳定后台通信的场景。

## CloseHandle 文件锁定

## RegSetValueA/RegSetValueExA 注册表