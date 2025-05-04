#include <stdio.h>
#include <stdlib.h>

struct demo {
    char string[8];

    void (*victim)();
};

void normal(struct demo *this) {
    puts("This is a normal function");
}

void abnormal(struct demo *this) {
    puts("hacked!");
}

int main() {
    struct demo *test = malloc(sizeof(struct demo));
    test->victim = normal;
    test->victim();
    free(test);
    //test=NULL;  // free后未置0
    test->victim = abnormal;
    test->victim();
}
