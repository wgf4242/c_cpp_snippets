cmake_minimum_required(VERSION 3.19)
project(c_project C)

set(CMAKE_C_STANDARD 99)
#add_executable(rc4  RC4.c)
# 遍历项目根目录下所有的 .c 文件
#file (GLOB files *.c **/*.c)

set(COUNT 1)
file (GLOB files *.c algorithm/*.c winapi/*.c)
foreach (file ${files})
    # 正则替换file的字符, 保存到exe
    set(EXE_NAME "exercise_c_${COUNT}")
    add_executable(${EXE_NAME} ${file})
    math(EXPR COUNT "${COUNT} + 1")
endforeach ()

#file (GLOB files dll/*.c ctf/**.c)
#foreach (file ${files})
#    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
#    add_library(${exe} SHARED ${file} ctf/reverse/moectf2022_checinsoup.c)
#    set_target_properties(${exe} PROPERTIES PREFIX "")       # 去掉lib前缀
#    #    add_executable (${exe} ${file} ccode/main.c)
#    message (\ \ \ \ --\ src/${exe}.c\ will\ be\ compiled\ to\ bin/${exe})
#endforeach ()

add_executable(md5 algorithm/md5/main.c algorithm/md5/md5.c)