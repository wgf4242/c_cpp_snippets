cmake_minimum_required(VERSION 3.30)
project(cmake_a06_unittest)

set(CMAKE_CXX_STANDARD 26)


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_mycode main.cpp)
target_link_libraries(test_mycode gtest_main)
# 多个时直接后面添加 add_executable(test_mycode main.cpp main1.cpp)

include(GoogleTest)
gtest_discover_tests(test_mycode)
