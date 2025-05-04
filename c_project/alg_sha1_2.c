#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <string.h>

void print_hash(unsigned char *hash, DWORD cbHash)
{
    for (DWORD i = 0; i < cbHash; i++)
    {
        printf("%02x", hash[i]);
    }
}

int main()
{
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        printf("Error: CryptAcquireContext() failed.\n");
        return 1;
    }

    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
    {
        printf("Error: CryptCreateHash() failed.\n");
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    char input[100];
    strcpy(input, "Hello, World!");

    if (!CryptHashData(hHash, (BYTE *)input, strlen(input), 0))
    {
        printf("Error: CryptHashData() failed.\n");
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    unsigned char hash[20];
    DWORD cbHash = 20;

    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &cbHash, 0))
    {
        printf("Error: CryptGetHashParam() failed.\n");
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    printf("Input: %s\n", input);
    printf("SHA1: ");
    print_hash(hash, cbHash);
    printf("\n");

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    return 0;
}