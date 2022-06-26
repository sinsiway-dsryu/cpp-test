#include <cstdio>
#include <cstdlib>
#include <cstring>
#define READ_STR_SIZE 16

// void setStrArray(char* str_arr[], int row, FILE* fp);
void setStrArray(char str_arr[][READ_STR_SIZE], int row, FILE* fp);
int getLineCount(FILE* fp);
int compare(const void *a, const void *b);

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("keywords.txt", "rt");
    if (fp == NULL) {
        puts("file open error");
        exit(1);
    }

    int row = getLineCount(fp);
    // char* str_arr[row];
    printf("row : %d\n", row);
    char str_arr[row][READ_STR_SIZE];
    setStrArray(str_arr, row, fp);
    printf("==== BEFORE ====\n");
    for (int i=0; i < row; i++) {
        printf("%s", &str_arr[i][READ_STR_SIZE]);
    }
    // qsort(*str_arr, row, READ_STR_SIZE, compare);
    qsort(str_arr, row + 1, READ_STR_SIZE, compare);

    // for (int i=0; i < row-1; i++) {
    //     compare(str_arr[i], str_arr[i+1]);
    //     // printf("%s", str_arr[i]);
    // }
    printf("==== AFTER ====\n");
    for (int i=0; i < row; i++) {
        printf("%s", &str_arr[i][READ_STR_SIZE]);
    }

    fclose(fp);
    // for (int i=0; i < row; i++) {
    //     free(str_arr[i]);
    // }
    return 0;
}

void setStrArray(char str_arr[][READ_STR_SIZE], int row, FILE* fp) {
    for(int i=0; i < row; i++) {
        // char* word = (char*)malloc(sizeof(char)* READ_STR_SIZE);
        memset(*str_arr, 0, sizeof(char)* READ_STR_SIZE);
        fgets(&str_arr[i][READ_STR_SIZE], READ_STR_SIZE, fp);
        // str_arr[i][READ_STR_SIZE] = *word;
    }
}

int getLineCount(FILE* fp) {
    int row = 0;
    while (!feof(fp)) {
        if (fgetc(fp) == '\n') row++;
    }
    fseek(fp, 0, SEEK_SET);
    return row;
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






