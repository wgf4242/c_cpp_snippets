# 环境配置

1. 默认选中提示第一项: 工具 - 选项 - 文本编辑器 - C/C++ - 高级,主动成员列表设置为TRUE即可。 默认需要 Tab完成补全

# 添加资源

1.右键项目->添加->资源->自定义->资源类型->BIN(想输入啥输入啥自定义的)->关闭添加窗口

在查找资源时 `    res = FindResource(NULL, MAKEINTRESOURCE(IDR_BIN4), L"BIN");` , 使用L"BIN"和上面对应


## 关闭随机地址
解决方案管理器-属性 (Ctrl+Shift+E - Alt+Enter) - 链接器 - 高级 - 随机基址 - 否


# 下载
## 国内加速
[Visual Studio 2022官网下载安装过慢的解决方法](https://blog.csdn.net/m0_55826602/article/details/127091733)

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

脱机安装所需的证书 - Certificates文件夹下



# 编译

## 常用设置
输出目录: $(SolutionDir)$(Platform)\$(Configuration)\

## 优化编译大小

启用代码优化
使用编译器的优化选项来减小代码大小。在 Visual Studio 中，可以在项目属性的“C/C++” -> “优化”中选择 /O1（最小化大小）选项。

使用静态链接:“C/C++” -> “代码生成”中设置“运行库”。
  多线程 DLL (MD): 减小 DLL 大小，依赖系统提供的运行时库。
  多线程 (MT):     增加 DLL 大小，但减少外部依赖。

5. 去除未使用的代码
使用链接器选项来移除未引用的函数和数据。在 Visual Studio 中，可以在“链接器” -> “优化” - 引用: 中启用“删除未引用的函数(/OPT:REF)”和“启用 COMDAT 消减(/OPT:ICF)”。

### FAQ
1. /O1”和“/RTC1”命令行选项不兼容
“C/C++” -> “代码生成”中设置“运行库” -> 默认
2. 

## Article

[基于已有项目配置Visual Studio新项目的C++库](https://mp.weixin.qq.com/s/EBy-HpI6S66cSun5pfiI7g)
