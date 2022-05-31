#include <cstdio>
#include <unistd.h>

#if 0
int main(int argc, char const *argv[])
{
    int pid = 0;
    int* pv1 = (int*)malloc(sizeof(int));

    *pv1 = 10;
    printf("before - pid : %d, pv1 : %d, p: %p\n", getpid(), *pv1, pv1);
    pid = fork();
    if(pid == 0) {
        *pv1 = 11;
        printf("11 - pid : %d, pv1 : %d, p: %p\n", getpid(), *pv1, pv1);
    } else if (pid !=0) {
        sleep(3);
        printf("10 - pid : %d, pv1 : %d, p: %p\n", getpid(), *pv1, pv1);
    }
    printf("pid : %d, pv1 : %d, p: %p\n", getpid(), *pv1, pv1);
    free(pv1);

    return 0;
}
#else
#include <cstdlib>
#include <csignal>
#define PROCESS_NUM 3

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("process.txt", "w+");
    if (fp == NULL) {
        puts("파일 오픈 실패");
        return -1;
    }

    for(int i=0; i < PROCESS_NUM; i++) {
        int pid = fork();
    }
    child(0, 2, fp);
    fclose(fp);
    return 0;
}
#endif
