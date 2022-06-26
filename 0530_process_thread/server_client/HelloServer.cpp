#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
// #include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 30
#define MAX_CLIENT 5

void signalHandle();
void childProcessHandler(int signal);
int initServer(int port);
int acceptClient(int server_sock);
void messageEcho(int sock, int fds[]);
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
    // signal handle
    signalHandle();
    // file
    int fds[2];
    pipe(fds);
    if (fork() == 0) {
        FILE* fp = fopen("echoMsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        for(int i=0; i < 10; i++) {
            int len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void*)msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }
    // accept and message echo
    while (true) {
        int client_sock = acceptClient(server_sock);
        if (client_sock == -1 && errno == EINTR) {
            puts("EINTR...continue...");
            continue;
        } else if (client_sock == -1) {
            errorHandler("accept() error.. client_sock : -1");
        }
        
        pid_t pid = fork();
        if (pid == 0) {
            close(server_sock);
            messageEcho(client_sock, fds);
            close(client_sock);
            printf("client disconnected...\n");
            
            return 0;
        } else if (pid > 0) {
            close(client_sock);
        } else {
            close(client_sock);
            continue;
        }
    }
    // server socket close
    close(server_sock);
    return 0;
}

void signalHandle() {
    // signal handling
    struct sigaction sigact;
    sigact.sa_handler = childProcessHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGCHLD, &sigact, 0);
}

void childProcessHandler(int signal) {
    int status;
    pid_t pid;
    // pid = waitpid(-1, &status, WNOHANG); 
    // pid = waitpid(-1, &status, 0); 
    pid = wait(&status); 
    if (pid == -1) {
        errorHandler("process wait failed");
    }
    if (WIFEXITED(status)) {
        printf("removed pid : %d\n", pid);
        printf("exit value  : %d\n", WEXITSTATUS(status));
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
    return  accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_size);
}

// message echo
void messageEcho(int sock, int fds[]) {
    char read_buffer[BUF_SIZE];
    int read_length;
    while ((read_length = read(sock, read_buffer, BUF_SIZE)) != 0) {
        write(sock, read_buffer, read_length);
        printf("pid : %d / read_length : %d\n", getpid(), read_length);
        write(fds[1], read_buffer, read_length);
    }
}

void errorHandler(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}