#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

int serverConnect(const char* ip, int port);
void errorHandler(const char* message);
void readRoutine(int sock);
void writeRoutine(int sock);

int main(int argc, char const *argv[])
{
    // required value check
    if (argc != 3) {
        printf("Usage : %s <ip> <port> \n", argv[0]);
        exit(1);
    }
    // server connection
    int sock = serverConnect(argv[1], atoi(argv[2]));

    pid_t pid = fork();
    if (pid == 0) {
        puts("connected...");
        // send to server
        writeRoutine(sock);
    } else if (pid > 0) {
        // receive from server
        readRoutine(sock);
    }
    // socket close
    close(sock);
    return 0;
}

int serverConnect(const char* ip, int port) {
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        errorHandler("socket() error");
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        errorHandler("connect() error");
    }

    return sock;
}

// message read routine
void readRoutine(int sock) {
    char read_buffer[BUF_SIZE];
    while (true) {
        int read_length = read(sock, &read_buffer, BUF_SIZE);
        if (read_length == 0) {
            return;
        }
        read_buffer[read_length] = 0;
        printf("Message from server : %s \n", read_buffer);
        // read_buffer[read_length-1] = '\0'; // 개행을 지우고 \0 (널)로 변경 
        // read_buffer[read_length+1] = '\0'; // 보내는 쪽에서 
    }
}

void writeRoutine(int sock) {
    char write_buffer[BUF_SIZE];
    while (true) {
        fgets(write_buffer, BUF_SIZE, stdin); // enter로 버퍼에 문장 입력
        if ((strcmp(write_buffer, "q\n") == 0) || (strcmp(write_buffer, "Q\n") == 0)) {
            shutdown(sock, SHUT_WR);
            return;
        }
        // fgets는 \n\0를 붙임, strlen은 \0을 빼고 카운트, \n까지 보내지 않으려면 strlen()-1
        if (write(sock, write_buffer, strlen(write_buffer)) == -1) {
            errorHandler("write() error");
        }
    }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}