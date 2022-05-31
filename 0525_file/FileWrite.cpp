#include <cstdio>
// #include <cstring>
#include <cstdlib>
#define MAX_STR_SIZE 100

int main(int argc, char const *argv[])
{
    char name[MAX_STR_SIZE];
    char account[MAX_STR_SIZE];
    char balance[MAX_STR_SIZE];
    FILE* fp = fopen("file2.txt", "at");
    if (fp == NULL) {
        puts("파일 오픈 실패");
        return -1;
    }
    system("clear"); // cstdlib, console command 
    printf("이름: ");
    scanf("%s", name);
    printf("계좌: ");
    scanf("%s", account);
    printf("잔액: ");
    scanf("%s", balance);

    fputs(name, fp);
    fputs("\t", fp);
    fputs(account, fp);
    fputs("\t", fp);
    fputs(balance, fp);
    fputs("\n", fp);

    fclose(fp);
    return 0;
}

