# 环境配置

1. 默认选中提示第一项: 工具 - 选项 - 文本编辑器 - C/C++ - 高级,主动成员列表设置为 TRUE 即可。 默认需要 Tab 完成补全
2. 使用 C++23: 项目 - 属性 - 常规 - C++语言标准

## vcpkg 添加包

vcpkg https://learn.microsoft.com/zh-cn/vcpkg/get_started/get-started-msbuild?pivots=shell-powershell

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg; .\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install

# 添加lz4
vcpkg install lz4
```



## 环境配置

### 工程: 新建文件夹

3. 新建文件夹: 右击工程 - 添加 - 筛选器

### 环境变量/调试启动目录

输出目录: 配置属性 - 常规 - 输出目录 配置 $(OutDir)变量
配置属性 - 调试 - 工作目录:  多项目时 $(SolutionDir)$(Platform)\$(Configuration)

### 无窗口运行

链接器->所有选项
->入口点->输入 mainCRTStartup
->子系统->窗口 Windows

### Include/Lib 目录

项目 - 属性 - VC++ - 包含目录/库目录

### 使用Python.h编译程序/无法打开文件“python310_d.lib”
[Windows下Visual Studio无法引入Python.h文件](https://blog.csdn.net/weixin_44575152/article/details/114186758)
`Cython2_pybind11\a01_pybind11_basic`

1.安装时√
√Precompile standard library
√Download debugging symbols
√Download debug binaries (requires VS 2017 or later)
2.Project->右键"属性"->VC++-> 包含目录 #配置 3.10.3\include\
3.Project->右键"属性"->VC++-> 库目录   #配置 3.10.3\libs
4.切换成配置的Debug/Release

```
#include <Python.h>

int main() {
    Py_Initialize();  // 初始化解释器
    // 执行Python相关操作
    Py_Finalize();    // 清理解释器资源
    return 0;
}
```

## DLL 调试

https://learn.microsoft.com/zh-cn/visualstudio/debugger/debugging-dll-projects?view=vs-2022
https://blog.csdn.net/caoshangpa/article/details/78733379



## 手动编译 cmd compiler

```
cl.exe Injector.cpp /link /OUT:Injector.exe
# x64 Native 启动时不需要下面
## 包括 windows.h
cl.exe Injector.cpp /I "%INCLUDE%" /I "%EXTERNAL_INCLUDE%" /link /LIBPATH:"%Lib%" /OUT:Injector.exe
# 编译 DLL
cl.exe /LD ProcessHider.cpp /link /OUT:ProcessHider.dll
```

# 快捷键

| Key           | Desc          |     |
| ------------- | ------------- | --- |
| Ctrl+J        | Snippets 提示 |     |
| Ctrl+K,Ctrl+X | Snippets 插入 |     |
| Ctrl+K,Ctrl+B | Snippets 管理 |     |
|               |               |     |

# 添加资源

1.右键项目->添加->资源->自定义->资源类型->BIN(想输入啥输入啥自定义的)->关闭添加窗口

在查找资源时 `    res = FindResource(NULL, MAKEINTRESOURCE(IDR_BIN4), L"BIN");` , 使用 L"BIN"和上面对应

## 关闭随机地址

解决方案管理器-属性 (Ctrl+Shift+E - Alt+Enter) - 链接器 - 高级 - 随机基址 - 否

## 添加 include .h 文件

放到 C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.42.34433\include

## Release 版本编译的反汇编代码不一样。

解决方案管理器-属性 (Ctrl+Shift+E - Alt+Enter)
配置 - 修改为 Release
配置属性 - C/C++ - 优化 - 已禁用

# 下载

## 国内加速

[Visual Studio 2022 官网下载安装过慢的解决方法](https://blog.csdn.net/m0_55826602/article/details/127091733)

```hosts
42.81.116.43 download.visualstudio.microsoft.com
```

## 离线下载

[组件](https://learn.microsoft.com/en-us/visualstudio/install/workload-and-component-ids)

```
# 下载全部
vs_Enterprise.exe --layout E:\VisualStudio2022(这里应该是你自己的目录) --all
# 桌面 Microsoft.VisualStudio.Workload.NativeDesktop
# .NET Microsoft.VisualStudio.Workload.ManagedDesktop
# 下载企业版
VisualStudioSetup.exe --layout g:\vsstudio --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --lang zh-CN
VisualStudioSetup.exe --layout g:\vsstudio --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --includeOptional --lang en-US
VisualStudioSetup.exe --layout e:\vsstudio --add Microsoft.VisualStudio.Component.CoreEditor --add Microsoft.VisualStudio.Workload.ManagedDesktop --add Microsoft.VisualStudio.Workload.NetCrossPlat --add Microsoft.VisualStudio.Workload.Universal --includeOptional --lang Zh-cn

# 安装
g:\vsstudio\vs_setup.exe
```

脱机安装所需的证书 - Certificates 文件夹下

# 编译
## 命令行

```sh
# 最小化
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cl testadd.c /Fe:TestAdd.exe /O1
# 禁止内联优化 有的函数就优化没了
cl testadd.c /Fe:TestAdd.exe /O1 /MT /Zi- /GS- /GL /Ob0
# 关闭随机地址
cl testadd.c /Fe:TestAdd.exe /O1 /MT /Zi- /GS- /GL /Ob0 /DYNAMICBASE:NO

# z7 将调试信息直接嵌入到生成的目标文件
cl -z7 main.c

# 禁用可执行文件的 地址空间布局随机化（ASLR）
editbin /DYNAMICBASE:NO m4_demo.exe
```
## 常用设置

输出目录: $(SolutionDir)$(Platform)\$(Configuration)\
输出文件: 链接器 - 常规 - 输出文件

## 优化编译大小

启用代码优化
使用编译器的优化选项来减小代码大小。在 Visual Studio 中，可以在项目属性的“C/C++” -> “优化”中选择 /O1（最小化大小）选项。

使用静态链接:“C/C++” -> “代码生成”中设置“运行库”。
多线程 DLL (MD): 减小 DLL 大小，依赖系统提供的运行时库。
多线程 (MT): 增加 DLL 大小，但减少外部依赖。

5. 去除未使用的代码
   使用链接器选项来移除未引用的函数和数据。在 Visual Studio 中，可以在“链接器” -> “优化” - 引用: 中启用“删除未引用的函数(/OPT:REF)”和“启用 COMDAT 消减(/OPT:ICF)”。

# FAQ

## 1. /O1”和“/RTC1”命令行选项不兼容

“C/C++” -> “代码生成”中设置“运行库” -> 默认

## .rc 文件查看代码

解决方案资源管理器 - 右击文件 - 查看代码（F7）

## .rc 文件显示有文件编辑器已经打开，实际上没有

需要刷新： xxx.rc 关闭展开，点箭头重新展开。

## “const char* 类型的实参与 LPCWSTR (aka const WCHAR*) 类型的形参不兼容” 错误

1.右击项目文件 - 属性 - 配置属性 - 高级 - 字符集 - 使用多字节字符集 
2. 配置属性的窗口上方 "配置" 上选 Debug, Release 分别改一次

## “to_string“: 不是 “std“ 的成员和“to_string”: 找不到标识符

```
#include <string>
```

## "char _" 类型的实参与 “LPWSTR” (aka "wchar_t _") 类型的形参不兼容

```
//wchar_t filename[MAX_PATH];
wchar_t filename[MAX_PATH];

//"const char *" 类型的实参与 "LPCWSTR" (aka "const WCHAR *") 类型的形参不兼容
//"example.dll"
L"example.dll"
```
## 资源resource.h更新了, 但是代码没有识别到控件

visual studio 关闭一下资源窗口， 按一下保存， 就能更新了。

## 【VS】常见错误：C4996 ‘fopen‘: This function or variable may be unsafe. Consider using fopen_s instead解决办法

https://blog.csdn.net/qq_40520596/article/details/107081505



# Article

[基于已有项目配置 Visual Studio 新项目的 C++库](https://mp.weixin.qq.com/s/EBy-HpI6S66cSun5pfiI7g)
