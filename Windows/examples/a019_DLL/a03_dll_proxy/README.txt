[利用DLL Proxying技术隐匿执行恶意代码](https://mp.weixin.qq.com/s/aAddba7UO-Uej_d5PMqZTQ)

2.3 自动生成代理Dll 文件
在我们执行DLL Proxying 的过程中，有些被劫持的DLL 文件可能有几十个导出函数，那这种情况下手动去添加转发预编译指令就显得很费时间。Github 上有个工具可以帮我们节省这个过程: https://github.com/Flangvik/SharpDllProxy