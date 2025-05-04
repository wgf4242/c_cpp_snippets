cmake_minimum_required(VERSION 3.30)
#set(CMAKE_C_COMPILER "D:/mingw/bin/gcc.exe")
#set(CMAKE_CXX_COMPILER "D:/mingw/bin/g++.exe")
project(printDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(printDemo main.cpp)
target_link_libraries(printDemo "D:\\mingw\\lib\\libstdc++exp.a")