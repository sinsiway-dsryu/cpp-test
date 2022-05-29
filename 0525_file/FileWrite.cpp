#include <cstdio>
#include <cstring>
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
    
    scanf("이름: %s", name);    
    scanf("계좌: %s", account);
    scanf("잔액: %s", balance);
    
    fputs(name, fp);
    fclose(fp);
    return 0;
}

