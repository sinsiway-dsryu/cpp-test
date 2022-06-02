#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESS_NUM 3

void childProcessWork(FILE* fp, int i);
void processKill(int pid);
int getRowPos(FILE* fp, int row);

int main(int argc, char const *argv[])
{
    // file open
    FILE* fp = fopen("process.txt", "w+");
    if (fp == NULL) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    // process fork init
    int pid[PROCESS_NUM];
    int status[PROCESS_NUM];
    memset(pid, 0, sizeof(pid));
    memset(status, 0, sizeof(status));

    for (int i=0; i < PROCESS_NUM; i++) {
        // process fork
        pid[i] = fork();
        if (pid[i] < 0) {
            perror("process fork() failed");
            exit(EXIT_FAILURE);
        }
        // child process processing
        if (pid[i] == 0) {
            childProcessWork(fp, i);
            return 0;
        } 
        // parent process processing
        // pid file write and waitpid
        if (pid[i] > 0) {
            fprintf(fp, "%d\n", pid[i]);
            fflush(fp);
            if (waitpid(pid[i], &status[i], WNOHANG) == -1) {
                perror("process wait failed");
                exit(EXIT_FAILURE);
            };
        } 
    }

    // process kill check
    for (int i=0; i < 5; i++) {
        system("ps -ef | grep Kill");
        sleep(1);
    }
    
    fclose(fp);
    return 0;
}

void childProcessWork(FILE* fp, int i) {
    switch (i)
    {
    case 0:
        printf("get pid[%d]: %d\n", i, getpid());
        sleep(10);
        break;
    case 1:
        printf("get pid[%d]: %d\n", i, getpid());
        sleep(10);
        break;
    case 2:
        printf("get pid[%d]: %d\n", i, getpid());
        sleep(2);
        // pid file read
        int target_pid = 0;
        int row_pos = getRowPos(fp, 2);
        fseek(fp, row_pos, SEEK_SET);
        fscanf(fp, "%d", &target_pid);
        // process kill
        processKill(target_pid);
        sleep(5);
        break;
    }
}

// process kill
void processKill(int pid) {
    printf("===== pid %d kills %d =====\n", getpid(), pid);
    if (kill(pid, SIGKILL) == -1) {
        perror("process kill failed");
        exit(EXIT_FAILURE);
    };
}

// find row pod
int getRowPos(FILE* fp, int row) {
    int count = 0;
    int pos = 0;
    fseek(fp, 0, SEEK_END);
    int file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    for (int i=0; i < file_length; i++) {
        if (fgetc(fp) == '\n') {
            count++;
            if (count == (row - 1)) {
                pos = i + 1; // row - 1 번째 \n의 다음 바이트
                break;
            }
        }
    }
    return pos; 
}