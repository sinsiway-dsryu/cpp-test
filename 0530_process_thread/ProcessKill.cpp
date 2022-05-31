#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid01;
    int pid02;
    int pid03;

    pid01 = fork();
    pid02 = fork();
    pid03 = fork();
    pause();

    printf("프로세스 끝 %d\n", getpid());
    return 0;
}
