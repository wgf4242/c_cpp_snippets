// [SIMD指令集实战：用C++榨干CPU最后1%的算力](https://mp.weixin.qq.com/s/lDvz5WXsDrkmHQawYESuEg)
// CMake
// set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse3")

// Visual Studio 设置 C++语言标准为最新
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>

float normal_sum(const float* arr, size_t n) {
    float sum = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return sum;
}



float sse_sum(const float* arr, size_t n) {
    __m128 sum = _mm_setzero_ps();
    for (size_t i = 0; i < n; i += 4) {
        __m128 vec = _mm_loadu_ps(arr + i);
        sum = _mm_add_ps(sum, vec);
    }

    // 水平相加
    sum = _mm_hadd_ps(sum, sum);
    sum = _mm_hadd_ps(sum, sum);

    float result;
    _mm_store_ss(&result, sum);
    return result;
}

int main(void) {
    setbuf(stdout, NULL);
    // 测试1000万元素数组 对比  normal_sum 和 sse_sum

    // 定义数组大小为 1000 万个元素
    size_t n = 10000000;
    float* arr = (float*)malloc(n * sizeof(float));
    if (!arr) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }

    // 使用随机数填充数组
    srand(time(NULL));
    for (size_t i = 0; i < n; ++i) {
        arr[i] = (float)rand() / RAND_MAX;
    }

    // 测试 normal_sum
    clock_t start = clock();
    float normal_result = normal_sum(arr, n);
    clock_t end = clock();
    double normal_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("normal_sum 结果: %f, 时间: %f 秒\n", normal_result, normal_time);

    // 测试 sse_sum
    start = clock();
    float sse_result = sse_sum(arr, n);
    end = clock();
    double sse_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("sse_sum 结果: %f, 时间: %f 秒\n", sse_result, sse_time);

    // 释放内存
    free(arr);

    return 0;
}
