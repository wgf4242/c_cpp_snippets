// https://mp.weixin.qq.com/s/JpwrE2LRYzBSzIaFl2TY9g
// gcc 40_thread_05_performance_test1.c -o test1 -lpthread
// time ./test1
// 比test2慢了一倍, 只是调整了data位置

#include <pthread.h>

struct {
    long a; // thread 1访问
    long b; // thread_2访问
    char data[64];
} data;

void *thread_1() {
    for (int i = 0; i < 1000000000; i++)
        data.a = 0xAAAA;
}

void *thread_2() {
    for (int i = 0; i < 1000000000; i++)
        data.b = 0xBBBB;
}

int main() {
    pthread_t id1, id2;

    pthread_create(&id1, NULL, (void *) thread_1, NULL);
    pthread_create(&id2, NULL, (void *) thread_2, NULL);
    //TODO: 需要进行CPU affinity设置才能100%保证两个线程运行在不同的CPU上
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    return 0;
}