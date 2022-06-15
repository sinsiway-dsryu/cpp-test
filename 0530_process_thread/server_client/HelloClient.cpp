#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

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
    printf("q를 입력해서 메시지 처리를 빠져나옴 - 접속소켓 : %d\n", sock);
    // socket close
    close(sock);
    printf("클라이언트 접속 소켓 닫음 이제 종료\n");
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
    char write_buffer[BUF_SIZE];
    char read_buffer[BUF_SIZE];

    while (true) {
        fputs("input message(Q to quit): ", stdout);
        fgets(write_buffer, BUF_SIZE, stdin); // enter로 버퍼에 문장 입력
        if ((strcmp(write_buffer, "q\n") == 0) || (strcmp(write_buffer, "Q\n") == 0)) {
            break;
        }
        // 문장 송신
        // fgets는 \n\0를 붙임, strlen은 \0을 빼고 카운트, \n까지 보내지 않으려면 strlen()-1
        int write_length = write(sock, write_buffer, strlen(write_buffer)-1);
        if (write_length == -1) {
                errorHandler("write() error");
        }
        // 문장 수신 - 나누어 수신하기
        int read_length = 0;
        while (read_length < write_length) { // 보낸 길이보다 작다면
            int read_count = read(sock, &read_buffer[read_length], 10); // 10바이트 씩 받기, 캐릭터 배열이라 바이트 수가 곧 인덱스
            if (read_count == -1) {
                errorHandler("read() error");
            }
            read_length += read_count;
        }
        // read_buffer[read_length-1] = '\0'; // 개행을 지우고 \0 (널)로 변경 
        // read_buffer[read_length+1] = '\0'; // 보내는 쪽에서 
        printf("Message from server : %s \n", read_buffer);
    }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}