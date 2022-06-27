#include <cstdio>
#include <cstdlib>
#include <cstring>
#define WORD_MAX_SIZE 16

struct List {
    Node* head;
    Node* current;
};

struct Node {
    Node* next;
    char* data;
};

List* initList(char* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->next = node;
    node->data = data;

    List* list = (List*)malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    list->head = node;
    list->current = node;

    return list;
}

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("keywords.txt", "rt");
    if (fp == NULL) {
        fputs("file open error", stderr);
        exit(1);
    }



    fscanf(fp, "%s", )


    return 0;
}
