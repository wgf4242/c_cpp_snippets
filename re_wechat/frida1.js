// Frida 脚本：Hook 微信好友列表，提取 wxid、昵称、头像信息 https://zhuanlan.zhihu.com/p/716874543
// 适用平台：Windows 微信

// Hook 配置信息（根据微信版本调整）
const hookConfig = {
    moduleName: "WeChatWin.dll",       // 目标模块名
    hookOffset: 0x2199925,             // Hook 地址偏移（十六进制）
    register: "rbp",                   // 基址寄存器
    offsets: {
        wxid: 0x340,                   // wxid 偏移
        nickname: 0x458,               // 昵称偏移
        avatar: 0x4b8                  // 头像偏移
    }
};

/**
 * 核心 Hook 函数：拦截好友列表相关函数，提取好友信息
 */
function hookFriendList() {
    try {
        // 获取模块基地址
        const moduleBase = Process.getModuleByName(hookConfig.moduleName).base;
        // 计算最终 Hook 地址（基地址 + 偏移）
        const hookAddress = moduleBase.add(hookConfig.hookOffset);
        
        console.log(`[+] 开始 Hook 微信好友列表，地址：${hookAddress}`);

        // 拦截目标函数
        Interceptor.attach(hookAddress, {
            onEnter: function(args) {
                try {
                    // 获取寄存器中的基指针
                    const basePointer = this.context[hookConfig.register];
                    
                    // 读取好友信息（UTF16 编码，微信字符串格式）
                    const friendInfo = {
                        wxid: basePointer.add(hookConfig.offsets.wxid).readPointer().readUtf16String(),
                        nickname: basePointer.add(hookConfig.offsets.nickname).readPointer().readUtf16String(),
                        avatar: basePointer.add(hookConfig.offsets.avatar).readPointer().readUtf16String()
                    };

                    // 控制台输出信息
                    console.log(`[好友信息] wxid: ${friendInfo.wxid}, 昵称: ${friendInfo.nickname}`);
                    // 发送信息到外部（如 Frida RPC 客户端）
                    send({ api: "recv_friend_list", data: friendInfo });

                } catch (error) {
                    // 捕获单条数据读取异常，不影响整体 Hook
                    console.error(`[-] 读取好友信息失败: ${error.stack}`);
                }
            }
        });

        console.log("[+] Hook 安装成功！");

    } catch (error) {
        console.error(`[-] Hook 安装失败: ${error.stack}`);
    }
}

/**
 * 入口函数：初始化 Hook
 */
function main() {
    console.log("[+] 微信好友列表 Hook 脚本启动");
    hookFriendList();
}

// 执行主函数
main();