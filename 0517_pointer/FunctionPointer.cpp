#include <cstdio>

void swap(int* a, int* b);
void sort(int arr[], size_t length, void (* swap)(int* a, int* b));

int main(int argc, char const *argv[])
{
    int arr[10] = { 2, 1, 3, 4, 5, 8, 7, 8, 9, 10 };
    size_t arr_length = sizeof arr / sizeof arr[0];
    void (*swap_func)(int* a, int* b);
    swap_func = swap;
    sort(arr, arr_length, swap_func);

    for (int i=0; i < arr_length; i++) {
        printf("arr : %d ", arr[i]);
        printf("\n");
    }
    return 0;
}

void sort(int arr[], size_t length, void (*swap_func)(int* a, int* b)) {
    for (int i=0; i < length-1; i++) {
        for (int j=i+1; j < length; j++) {
            if (arr[i] > arr[j]) {
                swap_func(&arr[i], &arr[j]);
            }
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
