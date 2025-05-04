#include <stdio.h>
#include <string.h>

char enc[] = "1234";

void bf(char *c, int cur, int bf_count) {
    if (cur == bf_count) {
        if (memcmp(c, enc, bf_count) == 0) {
            printf("Password found: %s\n", c);
        }
        return;
    }

    for (int i = 48; i < 127; ++i) {
        c[cur] = i;
        bf(c, cur + 1, bf_count);
    }
}

int main() {
    int bf_count = 4;
    char password[bf_count + 1];
    memset(password, 0, sizeof(password));

    bf(password, 0, bf_count);

    return 0;
}