#include <math.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define HASH_LENGTH 32
#define MAX_PASSWORD_LENGTH 10
#define LOG_INTERVAL 10000

// 定义用于生成可能密码的字符集
char CHARSET[] =
    "abcdefghijklmnopqrstuvwxyz0123456789";
#define CHARSET_LENGTH (sizeof(CHARSET) - 1)

// 根据索引生成密码字符串
static void index_to_password(char *password, unsigned long long index,
                              int password_length) {
  for (int i = password_length - 1; i >= 0; --i) {
    password[i] = CHARSET[index % CHARSET_LENGTH];
    index /= CHARSET_LENGTH;
  }
  password[password_length] = '\0';
}

int main(int argc, char **argv) {
  // 从命令行参数中读取哈希值
  unsigned char input_hash[HASH_LENGTH];
  for (int i = 0; i < HASH_LENGTH; i++) {
    sscanf(&argv[1][i * 2], "%2hhx", &input_hash[i]);
  }

  // 遍历所有可能的密码长度
  for (int password_length = 1; password_length <= MAX_PASSWORD_LENGTH;
       password_length++) {

    // 尝试当前长度的所有密码组合
    unsigned long long password_count = powl(CHARSET_LENGTH, password_length);
    for (long long index = 0; index < password_count; index++) {
      char password[MAX_PASSWORD_LENGTH + 1];
      index_to_password(password, index, password_length);
      if (index % LOG_INTERVAL == 0) {
        printf("Testing \"%s\"\n", password);
      }

      unsigned char hash[HASH_LENGTH];
      SHA256_CTX sha256;
      SHA256_Init(&sha256);
      SHA256_Update(&sha256, password, strlen(password));
      SHA256_Final(hash, &sha256);

      // 和用户输入的哈希值进行比对
      if (memcmp(hash, input_hash, HASH_LENGTH) == 0) {
        printf("Password found: %s\n", password);
        return 0;
      }
    }
  }

  return 0;
}
