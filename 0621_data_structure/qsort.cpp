#include <cstdio>
#include <cstdlib>
#include <cstring>
#define WORD_MAX_SIZE 16

int getLineCount(FILE* fp);
int compare(const void *a, const void *b);

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("keywords.txt", "rt");
    if (fp == NULL) {
        puts("file open error");
        exit(1);
    }
    // fscanf 사용하기 - fgets 사용시 printf(%s)로는 안보이나, qsort가 받는 배열 첫번째 요소가 \000 이 
    // char str_arr[15][WORD_MAX_SIZE];
    // int row = 0;
    // while (fscanf(fp, "%s", &str_arr[row][WORD_MAX_SIZE]) != EOF) {
    //     row++;
    // }

    // fread - buffer size full
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    char* file_buffer = (char*)malloc(sizeof(char) * file_size);
    if (file_buffer == NULL) {
        fputs("memory error", stderr);
        exit(2);
    }
    size_t file_read_size = fread(file_buffer, sizeof(char), file_size, fp);
    if (file_read_size != file_size) {
        fputs("file read error", stderr);
        exit(3);
    }
    int row = 0;
    for (int i = 0; i < file_read_size; i++) {
        if (file_buffer[i] == '\n') {
            row++;
        }
    }
    printf("row : %d\n", row);
    char str_arr[row][WORD_MAX_SIZE];
    memset(str_arr, 0, sizeof(str_arr));
    int char_index = 0;
    int str_index = 0;
    for (int i = 0; i < file_read_size; i++) {
        if (file_buffer[i] == '\n') {
            printf("str_arr : %s\n", &str_arr[str_index][WORD_MAX_SIZE]);
            char_index = 0;
            str_index++;
            continue;
        }
        str_arr[str_index][char_index] = file_buffer[i];
        printf("str_arr : %c\n", str_arr[str_index][char_index]);
        char_index++;
    }
    printf("char_index : %d\n", char_index);
    printf("str_index : %d\n", str_index);
    // char str_arr[row][WORD_MAX_SIZE];

    printf("==== BEFORE ====\n");
    // for (int i=0; i < str_index; i++) {
        // printf("%s\n", &str_arr[i][WORD_MAX_SIZE]);
    // }
    printf("%s\n", &str_arr[0][WORD_MAX_SIZE]);
    // qsort(str_arr, row, WORD_MAX_SIZE, compare);

    // printf("==== AFTER ====\n");
    // for (int i=0; i < row; i++) {
    //     printf("%s\n", &str_arr[i][WORD_MAX_SIZE]);
    // }
    
    // fread free
    free(file_buffer);

    fclose(fp);
    return 0;
}

// 아스키코드 순서로 정렬
// void compare(const void *a, const void *b) {
int compare(const void *a, const void *b) {
    char* str1 = (char*)a;
    // printf("str1 : %s",str1);
    char* str2 = (char*)b;
    // printf("str2 : %s",str2);
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            // printf("s1[%d] < s2[%d]\n", i, i);
            return -1;
        }
        if (str1[i] > str2[i]) {
            // printf("s1[%d] > s2[%d]\n", i, i);
            return 1;
        }
        if (str1[i] == str2[i]) {
            // printf("s1[%d] == s2[%d]\n", i, i);
            i++;
            continue;
        }
    }
    return 0;
}






