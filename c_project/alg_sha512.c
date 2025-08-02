// gcc -o encrypt.exe encrypt.c -lssl -lcrypto -fexec-charset=GBK
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MaxLenPlain 1024

int CryptData(unsigned char *pPlain, int LenPlain, char *pPass, unsigned char *pCrypt) {
    const int nTimes = 20000;
    int i;
    unsigned char hash_sha256[32];
    unsigned char hash_sha512[64];
    unsigned char Key[MaxLenPlain + 64];

    if (pPlain == NULL || pCrypt == NULL) return -1;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pPass, strlen(pPass));
    SHA256_Final(hash_sha256, &sha256);

    for (i = 0; i < nTimes; i++) {
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, hash_sha256, 32);
        SHA256_Final(hash_sha256, &sha256);
    }
    
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, pPass, strlen(pPass));
    SHA512_Final(hash_sha512, &sha512);

    for (i = 0; i < 64; i++)
        Key[i] = hash_sha512[i] ^ hash_sha256[i % 32];
    for (i = 0; i < LenPlain; i++)
        Key[i + 64] = Key[i] ^ Key[i + 2] ^ Key[i + 5] ^ Key[i + 6];
    for (i = 0; i < LenPlain; i++)
        pCrypt[i] = pPlain[i] ^ Key[i + 64];
    return 0;
}

int main() {
    char *message = "Come to the International Convention Center to discuss specific matters.";
    char *password = "9312";
    int len = strlen(message);
    unsigned char encrypted[MaxLenPlain];
    
    printf("原始消息: %s\n", message);
    printf("密码: %s\n", password);
    printf("消息长度: %d\n", len);
    
    int result = CryptData((unsigned char*)message, len, password, encrypted);
    
    if (result == 0) {
        printf("加密结果(16进制): ");
        for (int i = 0; i < len; i++) {
            printf("%02x", encrypted[i]);
        }
        printf("\n");
    } else {
        printf("加密失败\n");
    }
    
    return 0;
}