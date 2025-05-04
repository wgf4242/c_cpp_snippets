// gcc -shared -o random1.so random1.c
#include <stdlib.h>
#include <time.h>

void set_seed() {
    time_t seed = time(NULL);
    srand(seed);
}

int random_number() {
    return rand();
}

