#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 10
#define MAX_CLIENT 5

int initServer(int port);
int acceptClient(int server_sock);
void serverWork(int sock);
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
        serverWork(client_sock);
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
void serverWork(int sock) {
    char p_count;
    int count = 0;
    printf("Operand count: ");
    read(sock, &p_count, sizeof(p_count));
    if (p_count == 'c') {
        read(sock, &count, sizeof(count));
    }

    char p_op_arr = 'v';
    int op_arr[count];
    for (int i=0; i < count; i++) {
        printf("Operand %d: ", i);
        scanf("%d", &op_arr[i]);
    }

    char p_op = 'o';
    char op;
    
    // char write_buffer[BUF_SIZE];
    // char read_buffer[BUF_SIZE];
    // int read_length = 0;
    // while (read_length != 0) {
    //     read_length = read(sock, read_buffer, BUF_SIZE);
    //     if (read_length == -1) {
    //         errorHandler("read() error");
    //     }
    // }
    // if (write(sock, read_buffer, read_length) == -1) {
    //         errorHandler("write() error");
    // }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}