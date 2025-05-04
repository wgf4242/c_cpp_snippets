// test5.c
// gcc test5.c -o test5 -L. -ltest -lcrypto
#include "testlib.h"
#include <openssl/aes.h>

void importCryptoDemo()
{
    // The key to use for encryption
    AES_KEY enc_key;
    unsigned char key[AES_BLOCK_SIZE];
    memset(key, 0, AES_BLOCK_SIZE); // Zeroing the key

    AES_set_encrypt_key(key, 128, &enc_key);
}

int main(int argc, char *argv[])
{
    char *path;
    foo();
    importCryptoDemo();
    return 0;
}