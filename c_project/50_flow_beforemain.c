// https://gcc.gnu.org/onlinedocs/gcc-8.3.0/gcc/Common-Function-Attributes.html#Common-Function-Attributes
#include <stdio.h>

__attribute((constructor)) void before_main() {
    printf("%s\n", __FUNCTION__);
}

__attribute((destructor)) void after_main();

void after_main() {
    printf("%s\n", __FUNCTION__);
}


int main(int argc, char **argv) {
    printf("%s\n", __FUNCTION__);
    return 0;
}
