// 两步hook获取64位微信（3.9.11.25）好友列表 https://blog.csdn.net/jysatuo/article/details/141654414
let hook_info = {
    module_name: "WeChatWin.dll",
    hook_offset: "0x2199925", //根据微信版本, 更改位置
    register: "rbp",
    wxid_offset: "0x340",
    nickname_offset: "0x458",
    avatar_offset: "0x4b8"
}

//hook function
function hook_friend_list() {
    let hMod = Process.getModuleByName(hook_info.module_name).base;
    let Frid = hMod.add(hook_info.hook_offset);
    Interceptor.attach(Frid, {
        onEnter: function (args) {
            try {
                let base_pointer = this.context[hook_info.register];
                let result = {
                    wxid: base_pointer.add(hook_info.wxid_offset).readPointer().readUtf16String(),
                    nickname: base_pointer.add(hook_info.nickname_offset).readPointer().readUtf16String(),
                    avatar: base_pointer.add(hook_info.avatar_offset).readPointer().readUtf16String(),
                };
                console.log(result.wxid, result.nickname);
                send({api: "recv_friend_list", data: result})
            } catch (error) {
                console.error(error.stack)
            }
        }
    })
}

function entry() {
    try {
        hook_friend_list();
    } catch (error) {
        console.error(error.stack);
    }
}

entry()
