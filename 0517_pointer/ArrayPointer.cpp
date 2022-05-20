#include <cstdio>

void printArrayElement(int (*p_array)[5]);

int main(int argc, char const *argv[])
{
    int test_array[5][5];
    printf("input number 1 ~ 25 - test_array : ");
    for(int i=0; i < 5; i++) {
        for(int j=0; j < 5; j++) {
            scanf("%d", test_array[i] + j);
        }
    }
    printArrayElement(test_array);
    return 0;
}

//void printArrayElement(int (*p_array)[5]) 
void printArrayElement(int p_array[][5]) 
{
    printf("test array element 1 - 3 : %d\n", *(*(p_array + 1) + 3));
    printf("test array element 1 - 3 : %d\n", *p_array[1] + 3);
    printf("test array element 1 - 3 : %d\n", p_array[1][3]);
}