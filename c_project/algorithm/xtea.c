int trailingZeroes(int n) {
    int ans = 0;
    int d = 0;
    while (n) {
        d += n % 10;
        n /= 10;
        ans += n;
    }
    return ans + d;
}

#include <string.h>
#include "stdio.h"
#include<math.h>
int main(int argc, char *argv[], char **env) {
    setbuf(stdout, NULL);
    int d = pow(2, 27);
    printf("%lld\n", d);
    // int i = trailingZeroes(d);
    int i = trailingZeroes(134217728);
    printf("%lld\n", i);
    return 0;
}

// 5 4 3 2 1 = 20  6  = 120
// 10* 9 * 8 *7 *6 *5!=  3628800
