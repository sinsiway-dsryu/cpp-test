#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define MAX_CLIENT 5

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

    // accept and message echo
    for(int i=0; i < MAX_CLIENT; i++) {
        int client_sock = acceptClient(server_sock);
        printf("connected client %d\n", i+1);
        messageEcho(client_sock);
        close(client_sock);
    }

    // server socket close
    close(server_sock);

    return 0;
}

int initServer(int port) {
    int server_sock = socket(PF_INET, SOCK_STREAM, 0); // PF : IPv4 Protocol Family
    if (server_sock == -1) {
        errorHandler("socket() error");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // AF : IPv4 Address Family
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server_addr.sin_port = htons(port); // host to network short, ascii(char*) to integer

    if (bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        errorHandler("bind() error");
    }
    if (listen(server_sock, MAX_CLIENT) == -1) {
        errorHandler("listen() error");
    }
    return server_sock;
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
    // char write_buffer[BUF_SIZE];
    char read_buffer[BUF_SIZE];
    int read_length;
    while ((read_length = read(sock, read_buffer, BUF_SIZE)) != 0) {
        printf("read_length : %d\n", read_length);
        write(sock, read_buffer, read_length);
    }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}