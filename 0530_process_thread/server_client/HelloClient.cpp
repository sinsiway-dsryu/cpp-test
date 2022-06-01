#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int serverConnect(const char* ip, int port);
void messageReceive(int sock);
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
    messageReceive(sock);
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
    server_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        errorHandler("connect() error");
    }

    return sock;
}

// message receive from server by read
void messageReceive(int sock) {
    char message[30];
    memset(message, 0, sizeof(message));
    int read_length = read(sock, message, sizeof(message));
    if (read_length == -1) {
        errorHandler("read() error");
    }
    printf("Message from server : %s \n", message);
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}