#include <cstdio>
#include <cstring>

int main(int argc, char const *argv[])
{
    char buf[10];
    fputs("input: ",stdout);
    fgets(buf, 10, stdin);

    const char* t = "test";

    printf("strlen : %ld, str : %s\n", strlen(buf), buf);
    printf("strlen : %ld, str : %s\n", strlen(t), t);

    return 0;
}
