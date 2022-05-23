#include <cstdio>

int main(int argc, char const *argv[])
{
    unsigned char arr[2] = { 1, 1 };
    short result = arr[0];
    result <<= (sizeof arr[0])*8;
    result = result | arr[1];
    printf("%d", result);
    return 0;
}
