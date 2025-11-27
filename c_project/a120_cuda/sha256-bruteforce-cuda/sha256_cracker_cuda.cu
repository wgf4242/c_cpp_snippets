#include "sha256.cuh"
#include <cstdint>
#include <cuda.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#define HASH_LENGTH 32
#define MAX_PASSWORD_LENGTH 10
#define NUM_BLOCKS 512  // 线程块数量
#define NUM_THREADS 256 // 每个块中的线程数

// 定义用于生成密码组合的字符集
__constant__ char CHARSET[] =
    "abcdefghijklmnopqrstuvwxyz0123456789";
#define CHARSET_LENGTH (sizeof(CHARSET) - 1)

// 根据索引生成密码字符串
__device__ void index_to_password(char *password, uint64_t index,
                                  int password_length) {
  for (int i = password_length - 1; i >= 0; --i) {
    password[i] = CHARSET[index % CHARSET_LENGTH];
    index /= CHARSET_LENGTH;
  }
  password[password_length] = '\0';
}

// 用于在 GPU 设备上进行内存比较
__device__ int memcmp_device(const void *ptr1, const void *ptr2, size_t n) {
  const uint8_t *p1 = (const uint8_t *)ptr1;
  const uint8_t *p2 = (const uint8_t *)ptr2;
  for (size_t i = 0; i < n; ++i) {
    if (p1[i] != p2[i])
      return (int)p1[i] - (int)p2[i];
  }
  return 0;
}

__device__ int found = 0; // 标记是否已找到密码
__device__ char found_password[MAX_PASSWORD_LENGTH + 1];

__global__ void crack_sha256(const uint8_t *target_hash_device,
                             int password_length, uint64_t start_index, uint64_t password_count) { 
  uint64_t thread_index = blockIdx.x * blockDim.x + threadIdx.x;

  if (thread_index < password_count) {
    char password[MAX_PASSWORD_LENGTH + 1];
    index_to_password(password, start_index + thread_index, password_length);

    // 计算当前密码的哈希值
    uint8_t hash[HASH_LENGTH];
    SHA256_CTX sha256;
    sha256_init(&sha256);
    sha256_update(&sha256, (BYTE *)password, password_length);
    sha256_final(&sha256, hash);

    // 将当前密码的哈希值与用输入的哈希值进行比对
    if (memcmp_device(hash, target_hash_device, HASH_LENGTH) == 0) { 
      found = 1;
      for (int i = 0; i <= password_length; ++i) {
        found_password[i] = password[i];
      }
      return;
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <hash>\n", argv[0]);
    return 1;
  }

  // 从命令行参数中读取哈希值
  uint8_t target_hash[HASH_LENGTH];
  for (int i = 0; i < HASH_LENGTH; i++) {
    sscanf(&argv[1][i * 2], "%2hhx", &target_hash[i]);
  }

  // 将目标哈希复制到显存
  const uint8_t *target_hash_device;
  cudaMalloc((void **)&target_hash_device, HASH_LENGTH);
  cudaMemcpy((void *)target_hash_device, target_hash, HASH_LENGTH,
             cudaMemcpyHostToDevice);

  // 遍历所有可能的密码长度
  for (int password_length = 1; password_length <= MAX_PASSWORD_LENGTH;
       password_length++) {

    // 尝试当前长度的所有密码组合
    uint64_t password_count = powl(CHARSET_LENGTH, password_length);
    for (uint64_t start_index = 0; start_index < password_count;
         start_index += NUM_BLOCKS * NUM_THREADS) {

      // 通过 GPU 并行测试从 start_index 开始的各种密码组合
      crack_sha256<<<NUM_BLOCKS, NUM_THREADS>>>(target_hash_device,
                                                password_length, 
                                                start_index, 
                                                password_count);

      // 等待 GPU 执行完毕
      cudaDeviceSynchronize();

      // 读取显存中的标志位判断密码是否找到
      int host_found_flag;
      char host_found_password[MAX_PASSWORD_LENGTH + 1];
      cudaMemcpyFromSymbol(&host_found_flag, found, sizeof(int), 0,
                           cudaMemcpyDeviceToHost);
      if (host_found_flag) {
        cudaMemcpyFromSymbol(host_found_password, found_password,
                             MAX_PASSWORD_LENGTH + 1, 0,
                             cudaMemcpyDeviceToHost);
        printf("Password found: %s\n", host_found_password);
        goto cleanup;
      }
    }
  }

cleanup:
  cudaFree((void *)target_hash_device);

  return 0;
}
