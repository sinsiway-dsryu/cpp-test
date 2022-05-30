#include <cstdio>
#define LINE 255

int main(int argc, char const *argv[])
{
    char line[LINE+1];
    long file_length = 0;
    int row = 0;
    int pos = 0;
    FILE* fp = fopen("file1.txt", "rt");
    if (fp == NULL) {
        puts("파일 오픈 실패");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    for (int i=0; i < file_length; i++) {
        if (fgetc(fp) == '\n') {
            row++;
            if (row == 2) {
                pos = i + 1; // 3번째 \n의 다음 바이트
                break;
            }
        }
    }

    fseek(fp, pos, SEEK_SET);
    fgets(line, LINE, fp);
    printf("\n%s\n", line);

    fclose(fp);
    return 0;
}
