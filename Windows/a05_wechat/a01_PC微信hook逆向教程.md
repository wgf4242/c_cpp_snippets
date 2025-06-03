# [PC微信hook逆向教程](https://www.bilibili.com/video/BV1it411F7w8) (https://study.163.com/course/courseLearn.htm?courseId=1209558809#/learn/video?lessonId=1279878242&courseId=1209558809)
[Video | X86软件逆向分析实战（一）](https://www.bilibili.com/video/BV1PG4y1n7MB/) [L2](https://edu.csdn.net/learn/26500/336142)
[x86/x64软件逆向分析【提高篇】](https://edu.csdn.net/course/detail/32772)
[x86/x64软件逆向分析【拓展篇】](https://edu.csdn.net/course/detail/35817)

## 历史程序下载
* https://blog.csdn.net/qq_29607687/article/details/140651324
* [x64](https://github.com/tom-snow/wechat-windows-versions/releases)
* [x86](https://github.com/tom-snow/wechat-windows-versions-x86/releases)
* [android](https://github.com/DJB-Developer/wechat-android-history-versions)

## 课时3 寻找二维码地址
* [查找方式2](https://github.com/nick-zheng/WX_PC_HOOK/blob/master/11%E3%80%81HOOK%E7%99%BB%E5%BD%95%E4%BA%8C%E7%BB%B4%E7%A0%81%EF%BC%88%E4%BA%8C%EF%BC%89.md)
* [查找方式3](https://blog.csdn.net/weixin_44678558/article/details/129882431)
* [[易语言/CE/OD]利用Ultimap定位到微信实时消息并HOOK](https://www.bilibili.com/video/BV18Y4y1a747/)
* [日志消息找call | 实现收发消息](https://www.52pojie.cn/thread-1948799-1-1.html) https://www.52pojie.cn/thread-1948442-1-1.html

https://www.bilibili.com/video/BV1CA411N7EM/

1. 找二维码，PC端微信显示二维码后。
CE搜 IHDR 或16进制。 得到地址-C即PNG地址1 addr1。
2. 新建搜索 数值型 addr1

地址变化问题： 
  - OD附加WeChat, 运行
  - dd 地址1 05E8E60, 回车2次
  - 右击地址1 数值处, 内存写入
  - 扫码，再返回（此时会刷新二维码）
  - OD断下, 右击地址1 删除内存断点
  - 找到call写入图片。

Hook这里
```
地址	特征码	汇编代码
55DD19D2	E8 D984C900	call WeChatWi.56A69EB0
55DD19D7	83C4 0C     add esp,0xC

ESI 05E8B9B0
找到和地址1(5E8BE60)最近的，这里选ESI
Offset = ESI - 5E8BE60 = -4B0 可以双击左下数据窗口变成 $_偏移, 右击ESI跟随数据窗口)
5E8BE60 = ESI + 4B0
```
- 当前模块: 窗口标题: Wechat.exe m主线程, 模块 - WechatWin
- 单击e查看模块地址, 右击复制Wechatwin.dll的基址

55C80000, 模块基址

Hook偏移 = 1519D2
Call偏移 = DE9EB0

55DD19D2(call地址)-55C80000(模块地址) = 1519D2
call WeChatWi.56A69EB0 - 55C80000 = DE9EB0

## 课时4 实战读取二维码图片
汇编代码转换工具链接：https://pan.baidu.com/s/18GcxFUp6s9E46Zcx1VA6vg#2ssl

实现Hook输出图片。
OutputDebugStringA 在输出窗口能看到

见项目 名 c_cpp_tutorial\Windows\examples\a020_远程线程注入_DLL注入\a03_Project_dll_inject_hook

## 课时5 寻找登录信息地址
登录前（显示登录按钮的界面） 搜索 4字节0
登录后 搜索1
再退出 搜索0
直到确定地址范围到30个以内, 添加保留绿色地址。（即基址 可以动态计算出来）

因为状态函数登录成功会返回 True即1, 未登录会返回0

再测试下哪个比较快用哪个。 6AC0DCF4

* 打开OD附件到WeChat, 按运行
如果还是点不动。点击T图标, 右击 Resume all thread.

* dd 6AC0DCF4, 右击断点 - 内存写入断点， 运行断到 69D3603C, ECX=6AC0DCF4 准备在 69D36047 进行 Hook
* 找到位置 看后， 点击 e按钮， 找到WechatWin.dll， 右击 - 复制到剪贴板 - 基址
* Hookf地址69D36047 - 基址699A0000 = 396047
  - 69D36047 向上找有微信头像 6AC0DCF4 - 6AC0DBE4 = 110, 头像地址 = ECX-110h
  - 微信id=ECX-450h
- 没找到微信昵称, dc 6AC0DCF4
  - 昵称=ECX-3D8h

# 其他知识

WX使用的UI库是《Duilib》
二维码相关的关键词“qrcodeBackBtn

# FAQ
## OD附加后 CE只能打开进程不能附加
CE设置一下，调试器选项里面，用VEH调试，应该就可以同时附加了

0x 180000000
00018202F1E8 LoginSuccess
"FileUtils" 文件助手

90 73 57 0B 64 0E
0xB577390, 0xE64 地址+大小

QRCodeHelper::ScanQRCodeAsync
qrcodeBackBtn
.rdata:0000000184FA7BF0 aQrcodebackbtn:                         ; DATA XREF: sub_18202F8D0+263↑o
.text:000000018202FB33                 lea     rdx, aQrcodebackbtn ; "qrcodeBackBtn"
0x00007FFFDC8F1000 +0x202FB33

.text:0000000182030B47 48 8D 15 22 73 F7                 lea     rdx, aDoNewinitFinis ; "do Newinit finish"
.rdata:0000000184FA8618 4C 00 6F 00 67 00…                text "UTF-16LE", 'Login\login_Btn.png',0
.rdata:0000000184FA8640 6C 6F 67 20 65 72 aLogErrBothMain db 'log err, both mainwnd and loginwnd exist',0
.rdata:0000000184FA8640 72 2C 20 62 6F 74…                                 