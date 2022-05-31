#include <cstdio>
#define MAX_STR_SIZE 100

int main(int argc, char const *argv[])
{
    // char str_read[MAX_STR_SIZE];
    char str_read[MAX_STR_SIZE + 1]; // 문자열 100을 처리하기 위해, 마지막 null 값을 위한 1 바이트를 추가한다.
    FILE* fp = fopen("file1.txt", "rt");
    if (fp == NULL) {
        puts("파일 오픈 실패");
        return -1;
    }

    // while (feof(fp) == 0) {
    while (!feof(fp)) {
        // memset(str_read,0,MAX_STR_SIZE); 
        // fgets가 /n까지 넣어주고, printf의 "%s"도 그렇기에 괜찮다. scanf 도 마찬가지
        if (fgets(str_read, MAX_STR_SIZE, fp) != NULL) { // 굳이 if를 안써도 된다.
            printf("%s", str_read);
        };
    }

    fclose(fp);
    return 0;
}