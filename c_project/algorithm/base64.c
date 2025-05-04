#include <stdio.h>
#include <malloc.h>

union BASE64_ENCODE_DATA {
    char word[3];
    struct {
        unsigned base_3: 6;
        unsigned base_2: 6;
        unsigned base_1: 6;
        unsigned base_0: 6;
    };
};

void GetBaseData(char *strings, union BASE64_ENCODE_DATA *rt) {
    rt->word[2] = strings[0];
    rt->word[1] = strings[1];
    rt->word[0] = strings[2];

}

char baseTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *EnBase64(const char *strings) {
    unsigned length = -1;
    char *base64 = 0;
    unsigned baseCount = 0, icount;
    union BASE64_ENCODE_DATA baseData;
    char addchar = 0;
    while (strings[++length]);
    if (length > 0) {
        baseCount = (length + 2) / 3;
        addchar = (3 - (length % 3)) % 3;
        base64 = malloc(baseCount * 4 + 1);
        if (!base64)return base64;
        for (icount = 0; icount < baseCount; icount++) {
            GetBaseData(strings + 3 * icount, &baseData);
            base64[0 + icount * 4] = baseTable[baseData.base_0];
            base64[1 + icount * 4] = baseTable[baseData.base_1];
            base64[2 + icount * 4] = baseTable[baseData.base_2];
            base64[3 + icount * 4] = baseTable[baseData.base_3];
        }
        if (addchar != 0) {
            base64[baseCount * 4 - 1] = '=';
            if (addchar != 1)base64[baseCount * 4 - 2] = '=';
        }
    }
    base64[baseCount * 4] = 0;
    return base64;
}


int main(void) {
    setbuf(stdout, NULL);
    char text[65535];
    printf("请输入一段文字:\r\n");
    scanf("%s", text);
    char *base64 = EnBase64(text);
    printf("base64加密后>>%s", base64);
    free(base64);
}