#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 10

int serverConnect(const char* ip, int port);
void clientWork(int sock);
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
    clientWork(sock);
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
    puts("connected...");

    return sock;
}

// message receive from server by read
void clientWork(int sock) {
    char p_count = 'c';
    int count = 0;
    printf("Operand count: ");
    scanf("%d", &count);

    char p_op_arr = 'v';
    int op_arr[count];
    for (int i=0; i < count; i++) {
        printf("Operand %d: ", i);
        scanf("%d", &op_arr[i]);
    }

    char p_op = 'o';
    char op;
    printf("Operator: ");
    scanf("%c", &op);

    write(sock, &p_count, sizeof(p_count));
    write(sock, &count, sizeof(count));
    write(sock, &p_op_arr, sizeof(p_op_arr));
    write(sock, op_arr, sizeof(op_arr));
    write(sock, &p_op, sizeof(p_op));
    write(sock, &op, sizeof(op));

    int read_buf = 0;
    int read_count = 0;
    while ((read_count = read(sock, &read_buf, sizeof(read_buf))) != 0) {
        if (read_count == -1) {
            errorHandler("read() error");
        }
<<<<<<< HEAD
=======
        write(sock, write_buffer, strlen(write_buffer));
        int read_length = read(sock, read_buffer, BUF_SIZE);
        read_buffer[read_length-1] = '\0'; // 개행을 지우고 \0 (널)로 변경
        printf("Message from server : %s \n", read_buffer);
>>>>>>> a6b35a8645da01d188e65526488c2fa695ea4ffb
    }

    printf("Opertaion result : %d\n", read_buf);

    // char write_buffer[BUF_SIZE];
    // char read_buffer[BUF_SIZE];
    // while (true) {
    //     fputs("input message(Q to quit): ", stdout);
    //     fgets(write_buffer, BUF_SIZE, stdin);
    //     if ((strcmp(write_buffer, "q\n") == 0) || (strcmp(write_buffer, "Q\n") == 0)) {
    //         break;
    //     }
    //     // fgets는 \n\0를 붙임, \n을 보내지 않으려면 strlen()-1
    //     int write_length = write(sock, write_buffer, strlen(write_buffer)-1);
    //     if (write_length == -1) {
    //             errorHandler("write() error");
    //     }
    //     int read_length = 0;
    //     while (read_length < write_length) {
    //         int read_count = read(sock, &read_buffer[read_length], BUF_SIZE);
    //         if (read_count == -1) {
    //             errorHandler("read() error");
    //         }
    //         read_length += read_count;
    //     }
    //     read_buffer[read_length] = 0; // 긴 문장을 
    //     printf("Message from server : %s \n", read_buffer);
    // }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}