#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 10
#define MAX_CLIENT 5

void readChildProc(int sig);
int initServer(int port);
int acceptClient(int server_sock);
void messageEcho(int sock);
void errorHandler(const char* message);

int main(int argc, char const *argv[])
{
    // required value check
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    // server init
    int server_sock = initServer(atoi(argv[1]));

    // sigaction
    struct sigaction act;
    act.sa_handler = readChildProc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    // accept and message echo
    // for(int i=0; i < MAX_CLIENT; i++) {
    while (true) {
        int client_sock = acceptClient(server_sock);
        if (client_sock == -1) continue;
        puts("new client connected...");
        pid_t pid = fork();
        if (pid < 0) {
            close(client_sock);
            continue;
        }
        if (pid == 0) {
            close(server_sock);
            // printf("client connected - %d\n", i);
            messageEcho(client_sock);
            close(client_sock);
            // printf("client disconnected - %d\n", i);
            puts("client disconnected...");
            exit(0);
        }
        if (pid > 0) {
            close(client_sock);
        }
    }
    // server socket close
    close(server_sock);
    return 0;
}

void readChildProc(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    // pid_t pid = wait(&status);
    // pid = wait(&status);
    // pid = wait(&status); // wait 를 걸면, 여기서 메인이 hang 걸리면서 멈추긴 한다. 당연히 accept도 더이상 불가
    // 교재는 sigaction에 넘기는 이벤트 핸들러 안에서 waitpid를 잡으라고만 나오는데,
    // 하나의 자식프로세스라도 messageEcho가 끝나면, main이 끝나버리면서 for문에 걸려 있어야 할..
    if (pid == -1) {
        errorHandler("process wait failed");
    }
    if (WIFEXITED(status)) {
        printf("removed proc id : %d\n", pid);
        printf("child proc send : %d\n", WEXITSTATUS(status));
    }
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
    
    int client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_size);
    if (client_sock == -1) {
        errorHandler("accept() error");
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
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}