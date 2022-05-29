#include <cstdio>
#include <cstring>
#define MAX_STR_SIZE 100

int main(int argc, char const *argv[])
{
    char str_read[MAX_STR_SIZE];
    FILE* fp = fopen("file1.txt", "rt");
    if (fp == NULL) {
        puts("파일 오픈 실패");
        return -1;
    }

    while (feof(fp) == 0) {
        // memset(str_read,0,MAX_STR_SIZE); 
        // fgets가 /n까지 넣어주고, printf의 "%s"도 그렇기에 괜찮다?
        if (fgets(str_read, MAX_STR_SIZE, fp) != NULL) {
            printf("%s", str_read);
        };
    }

    fclose(fp);
    return 0;
}
