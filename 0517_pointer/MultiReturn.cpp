#include <cstdio>


void testFunc(int* a, int* b, int* c);
void innerTestFunc(int* a, int* b, int* c);

int main(int argc, char const *argv[])
{
    int a = 1;
    int b = 2;
    int c = 3;
    printf("parameter values : %d, %d, %d\n", a, b, c);
    testFunc(&a, &b, &c);
    printf("test function result : %d, %d, %d\n", a, b, c);
    
    return 0;
}

void testFunc(int* a, int* b, int* c) {
    innerTestFunc(a, b, c);
}

void innerTestFunc(int* a, int* b, int* c) {
    *a += 1;
    *b += 1;
    *c += 1;
}

