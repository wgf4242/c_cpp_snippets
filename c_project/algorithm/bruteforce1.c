#include <stdio.h>

void bf(size_t count, char start, char anEnd, void (*callback)(const char *), char *enc);
void print_combination(const char *combination);

int main() {
    size_t count = 3;
    // char start = 0x20, end = 0x7f;
    char start = 'a', end = 'd';
    char enc[] = "abc";

    bf(count, start, end, print_combination, NULL);
    return 0;
}

void bf(size_t count, char start, char anEnd, void (*callback)(const char *), char *enc) {
    char arr[count + 1];
    arr[count] = '\0';

    for (size_t i = 0; i < count; ++i) {
        arr[i] = start;
    }

    while (1) {
        (*callback)(arr);

        ssize_t j;
        for (j = count - 1; j >= 0; --j) {
            if (arr[j] == anEnd) {
                if (j == 0) return; // 已完成
                arr[j] = start;
            } else {
                arr[j]++;
                break;
            }
        }
    }
}

void print_combination(const char *combination) {
    printf("%s\n", combination);
}
