#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

int serverConnect(const char* ip, int port);
void messageEcho(int sock);
void errorHandler(const char* message);

int main(int argc, char const *argv[])
{
    // required value check
    if (argc != 3) {
        printf("Usage : %s <ip> <port> \n", argv[0]);
        exit(1);
    }
    // server connection
    int sock = serverConnect(argv[1], atoi(argv[2]));
    // receive from server
    messageEcho(sock);
    // socket close
    close(sock);

    return 0;
}

int serverConnect(const char* ip, int port) {
    struct sockaddr_in server_addr;
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        errorHandler("socket() error");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    // inet_aton(ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        errorHandler("connect() error");
    }
    puts("connected...");

    return sock;
}

// message receive from server by read
void messageEcho(int sock) {
    char write_buffer[BUF_SIZE];
    char read_buffer[BUF_SIZE];
    while(true) {
        fputs("input message(Q to quit): ", stdout);
        fgets(write_buffer, BUF_SIZE, stdin);
        if ((strcmp(write_buffer, "q\n") == 0) || (strcmp(write_buffer, "Q\n") == 0)) {
            break;
        }
        printf("write_length : %lu\n", strlen(write_buffer));
        write(sock, write_buffer, strlen(write_buffer));
        int read_length = read(sock, read_buffer, BUF_SIZE-1);
        printf("read_length : %d\n", read_length);
        read_buffer[read_length] = 0;
        printf("Message from server : %s \n", read_buffer);
    }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}