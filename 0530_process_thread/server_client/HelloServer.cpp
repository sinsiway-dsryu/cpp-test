#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int initServer(int port);
int acceptClient(int server_sock);
void messageSend(int client_sock, const char* message, size_t message_length);
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
    // accept
    int client_sock = acceptClient(server_sock);
    // send to client
    char msg[30] = "hello_world!";
    messageSend(client_sock, msg, sizeof(msg));
    // socket close
    close(client_sock);
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
    if (listen(server_sock, 5) == -1) {
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

// message send client by write
void messageSend(int client_sock, const char* message, size_t message_length) {
    write(client_sock, message, message_length);
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}