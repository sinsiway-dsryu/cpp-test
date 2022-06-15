#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
// #include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 10
#define MAX_CLIENT 10

void childProcessHandler(int signal);
int initServer(int port);
int acceptClient(int server_sock);
void messageEcho(int sock);
void errorHandler(const char* message);

int main(int argc, char const *argv[])
{
    // signal handling
    struct sigaction sigact;
    sigact.sa_handler = childProcessHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGCHLD, &sigact, 0);
    // required value check
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    // server init
    int server_sock = initServer(atoi(argv[1]));
    // accept and message echo
    for(int i=0; i < MAX_CLIENT; i++) {
        // int client_sock = acceptClient(server_sock);
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        printf("=== 서버 소켓으로 accept client 대기 들어가기 : %d\n", server_sock);
        int client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_size);
        printf("==== 서버 소켓으로 accept client 처리 완료 server_sock : %d, client_sock : %d\n", server_sock, client_sock);
        if (client_sock == -1 && errno == EINTR) {
            puts("EINTR...continue...");
            continue;
        } else if (client_sock == -1) {
            errorHandler("accept() error.. client_sock : -1");
        }
        
        pid_t pid = fork();
        if (pid < 0) {
            close(client_sock);
            errorHandler("process fork error");
        } else if (pid == 0) {
            printf("자식 프로세스 입니다. pid : %d, 서버소켓 닫기 : %d\n", pid, server_sock);
            close(server_sock);
            printf("자식 프로세스 클라이언트 접속 - 순번 : %d\n", i);
            messageEcho(client_sock);
            printf("자식 프로세스 에코 서비스 종료 - 소켓닫기 전: %d\n", client_sock);
            close(client_sock);
            printf("자식 프로세스 클라이언트 접속 종료 - 순번 : %d\n", i);
            exit(0);
        } else if (pid > 0) {
            printf("부모 프로세스가 보는 자식 프로세스의 pid : %d\n", pid);
            printf("부모 프로세스는 사용한 클라이언트 소켓 닫기 : %d\n", client_sock);
            close(client_sock);
        }
    }
    // server socket close
    close(server_sock);
    return 0;
}

void childProcessHandler(int signal) {
    int status;
    pid_t pid;
    printf("핸들러의 waitpid 처리 시작\n");
    // pid = waitpid(-1, &status, WNOHANG); 
    // pid = waitpid(-1, &status, 0); 
    pid = wait(&status); 
        // printf("waitpid - while 문 진입\n");
    if (pid == -1) {
        errorHandler("process wait failed");
    }
    if (WIFEXITED(status)) {
        printf("removed pid : %d\n", pid);
        printf("exit value  : %d\n", WEXITSTATUS(status));
    }
    printf("waitpid - 정보 출력 완료\n");
    // printf("waitpid - while 문 종료\n");
}

int initServer(int port) {
    int sock = socket(PF_INET, SOCK_STREAM, 0); // PF : IPv4 Protocol Family
    if (sock == -1) {
        errorHandler("socket() error");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // AF : IPv4 Address Family
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server_addr.sin_port = htons(port); // host to network short, ascii(char*) to integer

    if (bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        errorHandler("bind() error");
    }
    if (listen(sock, MAX_CLIENT) == -1) {
        errorHandler("listen() error");
    }
    return sock;
}

int acceptClient(int server_sock) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    printf("=== 서버 소켓으로 accept client 대기 들어가기 : %d\n", server_sock);
    int client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_size);
    printf("==== 서버 소켓으로 accept client 처리 완료 server_sock : %d, client_sock : %d\n", server_sock, client_sock);
    if (client_sock == -1) {
        errorHandler("accept() error.. client_sock : -1");
    }
    return client_sock;
}

// message echo
void messageEcho(int sock) {
    char read_buffer[BUF_SIZE];
    int read_length;
    while ((read_length = read(sock, read_buffer, BUF_SIZE)) != 0) {
        write(sock, read_buffer, read_length);
        printf("pid : %d / read_length : %d\n", getpid(), read_length);
    }
    printf("자식 프로세스 에코 함수 종료 - client sock : %d\n", sock);
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}