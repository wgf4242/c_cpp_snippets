#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RC4
void RC4Init(unsigned char *rc4box, const char *key, unsigned int keylen) {
    char k[256];
    for (int i = 0; i < 256; i++) {
        rc4box[i] = i;
        k[i] = key[i % keylen];
    }
    for (int i = 0, j = 0; i < 256; i++) {
        j = (j + rc4box[i] + k[i]) & 0xff;
        int tmp = rc4box[i];
        rc4box[i] = rc4box[j];
        rc4box[j] = tmp;
    }
}

void RC4Crypt(unsigned char *rc4box, char *src, unsigned int len) {
    for (int i = 0, j = 0, k = 0; k < len; k++) {
        i = (i + 1) & 0xff;
        j = (j + rc4box[i]) & 0xff;
        int tmp = rc4box[i];
        rc4box[i] = rc4box[j];
        rc4box[j] = tmp;
        src[k] ^= rc4box[(rc4box[i] + rc4box[j]) & 0xff];
    }
}

void rc4_do_crypt(void *buf, size_t buf_len, const void *key, size_t key_len) {
    unsigned char rc4box[256];
    RC4Init(rc4box, (const char *) key, key_len);
    RC4Crypt(rc4box, (char *) buf, buf_len);
}

#define _QWORD unsigned long long
#define _DWORD unsigned int
#define _WORD unsigned short

int main() {
    unsigned char enc[30];
    *(_DWORD *) enc = 0xF4DD0F64;
    *(_DWORD *) &enc[4] = 0x5173B9F8;
    *(_DWORD *) &enc[8] = 0xC7D238B2;
    *(_DWORD *) &enc[12] = 0x9B9FCA8;
    *(_DWORD *) &enc[16] = 0x286D3C51;
    *(_DWORD *) &enc[20] = 0x429DE399;
    *(_DWORD *) &enc[24] = 0x8084307B;
    *(_WORD *) &enc[28] = 0x9175;
    const char *data = "flag{tH14.l4_F@kKkEeeE---f41g}";
    for (int i = 0; i < 30; i++)
        enc[i] ^= data[i];

    unsigned char keystream[32];
    char key[8];
    memset(key, 0, 8);
    for (int a = 0x20; a < 0x7f; a++) {
        key[3] = a;
        for (int b = 0x20; b < 0x7f; b++) {
            key[2] = b;
            for (int c = 0x20; c < 0x7f; c++) {
                printf("\r%02x%02x%02x", a, b, c);
                key[1] = c;
                for (int d = 0x20; d < 0x7f; d++) {
                    key[0] = d;
                    memset(keystream, 0, sizeof(keystream));
                    rc4_do_crypt(keystream, 30, &key, 4);
                    if (!memcmp(keystream, enc, 30)) {
                        printf("\n%s\n", key);
                        return 0;
                    }
                }
            }
        }
    }
    puts("\nNot Found!");
    return -1;
}
