#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p1, *p2, *p3, *p4, *p5;
    size_t fake_chunk[4];
    fake_chunk[0] = 0;
    fake_chunk[1] = 0x70;
    p1 = malloc(0x60);
    p2 = malloc(0x60);
    free(p1);
    free(p2);
    free(p1);

    return 0;
}
