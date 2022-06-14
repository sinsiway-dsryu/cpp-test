#include <cstdio>
#include <pthread.h>

void* threadMain(void *arg);

int main(int argc, char const *argv[])
{
    int number = 0;

    pthread_t tid01, tid02;
    pthread_create(&tid01, NULL, threadMain, (void *)&number);
    pthread_create(&tid02, NULL, threadMain, (void *)&number);

    pthread_join(tid01, NULL);
    pthread_join(tid02, NULL);

    printf("result : %d\n", number);
    return 0;
}

void* threadMain(void *arg) {
    for (int i=0; i < 500; i++) {
        (*(int *)arg)++;
        printf("i - %d, number - %d\n", i, (*(int *)arg));
    }

    return NULL;
}
