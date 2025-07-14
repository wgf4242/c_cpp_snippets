[企业微信HOOK逆向（sdk）——登录二维码api](https://www.cnblogs.com/cnzryblog/p/16016850.html)

# 企业微信
[企业微信 - 白日梦之获取登录二维码](https://bbs.kanxue.com/thread-287381.htm)
[[原创]2025企业微信4.1.36.6011刷新二维码](https://bbs.kanxue.com/thread-286472.htm)

* [批量自动添加好友](https://www.cnblogs.com/cnzryblog/p/14742232.html)
* [企业微信PC版hook源码api接口](https://juejin.cn/post/7100373217742684173)
* [企业微信机器人sdk接口api之发送文章消息](https://juejin.cn/post/6988404078875246629)
* [企业微信机器人](https://www.cnblogs.com/wwgk/p/14928492.html)
* [企业微信所用技术和分析思路](https://www.cnblogs.com/wwgk/p/14808896.html)
* [企业微信HOOK逆向（PC端）——接收消息](https://www.cnblogs.com/cnzryblog)
* [企业微信PC版4.0 HOOK逆向sdk接口api](https://www.cnblogs.com/hwmytr/articles/16850302.html)
# Example

## 1. Hook二维码

x32dbg 打开企业微信, `bp kernelbase.CreateFileW` 条件断点  `strstr(utf16(ptr(esp+4)),"WXWorkLocal\Global") == 1` 查看直到有 `WXWorkLocal\Global\Image\08a71595-8544-49c6-be2f-887bc46eacdf.png` 这种路径
