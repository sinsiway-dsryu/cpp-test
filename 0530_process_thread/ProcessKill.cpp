#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESS_NUM 3

int getRowPos(FILE* fp, int row);

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("process.txt", "w+");
    if (fp == NULL) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    int pid[PROCESS_NUM];
    int ret[PROCESS_NUM];
    int status[PROCESS_NUM];
    memset(pid, 0, sizeof(pid));
    memset(ret, 0, sizeof(ret));
    memset(status, 0, sizeof(status));

    for (int i=0; i < PROCESS_NUM; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror("process fork() failed");
            exit(EXIT_FAILURE);
        } else if (pid[i] == 0) {
            // do child stuff
            if (i == 0) {
                printf("get pid[%d]: %d\n", i, getpid());
                sleep(10);
            }
            if (i == 1) {
                printf("get pid[%d]: %d\n", i, getpid());
                sleep(10);
            }
            if (i == 2) {
                printf("get pid[%d]: %d\n", i, getpid());
                sleep(2);
                int target_pid = 0;
                int row_pos = getRowPos(fp, 2);
                fseek(fp, row_pos, SEEK_SET);
                fscanf(fp, "%d", &target_pid);
                printf("pid %d kills %d\n", getpid(), target_pid);
                if (kill(target_pid, SIGKILL) == -1) {
                    perror("process kill failed");
                    exit(EXIT_FAILURE);
                };
                sleep(8);
            }
            return 0;
        } else if (pid[i] > 0) {
            // printf("getpid: %d / pid[%d]: %d\n", getpid(), i, pid[i]);
            fprintf(fp, "%d\n", pid[i]);
            fflush(fp);
            // if (i == 0 || i == 1 || i == 2) {
            ret[i] = waitpid(pid[i], &status[i], WNOHANG);
            // }
            // if (i == 2) {
                // ret[i] = waitpid(pid[i], &status[i], 0);
            // }
        } 
    }

    // WIFEXITED - 자식 프로세스 정상 종료 시 true(1)
    // WEXITSTATUS - 자식 프로세스의 return
    // WIFSIGNALED - 자식 프로세스 비정상 종료 시 true
    // WTERMSIG - 자식 프로세스의 비정상 종료 이유
    // for (int i=0; i < PROCESS_NUM; i++) {
        // printf("getpid: %d, ret : %d, WIFEXITED : %d, WEXITSTATUS : %d, WIFSIGNALED : %d, WTERMSIG : %d\n",
            // getpid(), ret[i], WIFEXITED(status[i]), WEXITSTATUS(status[i]), WIFSIGNALED(status[i]), WTERMSIG(status[i]));
    // }
    for (int i=0; i < 5; i++) {
        system("ps -ef | grep Kill");
        sleep(1);
    }
    fclose(fp);
    return 0;
}

// 원하는 라인 시작 위치 찾기
// row 는 1 부터 시작
// row : 3 -> 3 번째 줄 시작 위치 반환
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