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
    // fscanf 사용하기 - qsort가 받는 배열 첫번째 요소가 \000 가 된다. 아래처럼 하면,
    // &str_arr[row][WORD_MAX_SIZE] 가 아니라 str_arr[row] 다..
    // char str_arr[15][WORD_MAX_SIZE];
    // int row = 0;
    // while (fscanf(fp, "%s", &str_arr[row][WORD_MAX_SIZE]) != EOF) {
    //     row++;
    // }

    // fread - 파일 크기와 같은 버퍼 만들어서 받기
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    char* file_buffer = (char*)malloc(sizeof(char) * file_size);
    if (fread(file_buffer, sizeof(char), file_size, fp) != file_size) {
        fputs("file read error", stderr);
        exit(3);
    }
    // 개행 기준 문장 개수 확인
    int row = 0;
    for (int i = 0; i < file_size; i++) {
        if (file_buffer[i] == '\n') {
            row++;
        }
    }
    printf("row : %d\n", row);
    // 2차원 배열에 한 char씩 널까지, 개행 만 빼고 입력
    char str_arr[row][WORD_MAX_SIZE];
    memset(str_arr, 0, sizeof(str_arr));
    int char_index = 0;
    int str_index = 0;
    for (int i = 0; i < file_size; i++) {
        if (file_buffer[i] == '\n') {
            char_index = 0;
            str_index++;
            continue;
        }
        str_arr[str_index][char_index] = file_buffer[i];
        char_index++;
    }

    // 정렬 전 출력
    printf("==== BEFORE ====\n");
    for (int i=0; i < str_index; i++) {
        printf("%s\n", str_arr[i]);
    }
    // strcasecmp 소문자 대응 - 대소문자 사이 특수문자의 값 변경
    // for (int i=0; i < str_index; i++) {
    //     for (int j=0; j < WORD_MAX_SIZE; j++) {
    //         if (str_arr[i][j] > 90 && str_arr[i][j] < 97) {
    //             printf("before : %d\n", str_arr[i][j]);
    //             str_arr[i][j] += 32;
    //             printf("before : %d\n", str_arr[i][j]);
    //         }
    //     }
    // }
    // 정렬
    qsort(str_arr, row, WORD_MAX_SIZE, compare);
    // strcasecmp 소문자 대응 - 값 변경한 특수문자 되돌리기
    // for (int i=0; i < str_index; i++) {
    //     for (int j=0; j < WORD_MAX_SIZE; j++) {
    //         if (str_arr[i][j] > 122 && str_arr[i][j] < 129) {
    //             printf("before : %d\n", str_arr[i][j]);
    //             str_arr[i][j] -= 32;
    //             printf("before : %d\n", str_arr[i][j]);
    //         }
    //     }
    // }
    // 정렬 후 출력
    printf("==== AFTER ====\n");
    for (int i=0; i < row; i++) {
        printf("%s\n", str_arr[i]);
    }
    
    // 문자열 입력 받아 bsearch
    // char input_str[WORD_MAX_SIZE];
    // printf("input word : ");
    // scanf("%s", input_str);
    // char *find_str;
    // if ((find_str = (char*)bsearch(input_str, str_arr, row, WORD_MAX_SIZE, compare)) != NULL) {
    //     printf("find : %s\n", find_str);
    // } else {
    //     printf("not found\n");
    // }

    // free, close
    free(file_buffer);
    fclose(fp);
    return 0;
}

// 아스키코드 순서로 정렬
int compare(const void *a, const void *b) {
    char* str1 = (char*)a;
    char* str2 = (char*)b;
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        }
        if (str1[i] > str2[i]) {
            return 1;
        }
        if (str1[i] == str2[i]) {
            i++;
            continue;
        }
    }
    return 0;
    // return strcmp((char*)a, (char*)b);
    // return strcasecmp((char*)a, (char*)b);
}





