#include <cstdio>
#include <cstdlib>
#include <cstring>
#define WORD_MAX_SIZE 16

struct Node {
    Node* next_node;
    char* node_data;
};

struct List {
    Node* head_node;
    Node* tail_node;
};

Node* newNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->node_data = (char*)malloc(sizeof(char) * WORD_MAX_SIZE);
    memset(node->node_data, 0, sizeof(char) * WORD_MAX_SIZE);
    node->next_node = NULL;
    return node;
}

void deleteNode(Node* node) {
    free(node->node_data);
    free(node);
}

List* newList() {
    Node* new_node = newNode();
    List* list = (List*)malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    list->head_node = new_node;
    list->tail_node = new_node;
    return list;
}

void deleteList(List* list) {
    Node* target_node;
    while (list->head_node != list->tail_node) {
        target_node = list->head_node;
        list->head_node = list->head_node->next_node;
        deleteNode(target_node);
    }
    deleteNode(list->tail_node);
    free(list);
}

// Node* addNode(Node* before_node, List* list) {
Node* addNode(List* list) {
    // Node* new_node = newNode();
    // before_node->next_node = new_node;
    // list->tail_node = new_node;
    // return new_node;
    list->tail_node->next_node = newNode();
    list->tail_node = list->tail_node->next_node;
    return list->tail_node;
}

void removeNode(const char* node_data, List* list) {
    Node* find_node = list->head_node;
    Node* before_node = NULL;
    // while (find_node != NULL) { // 마지막 노드까지 찾기위해, find_node가 NULL이 되어야 끝나도록 조건 정의. while 조건에 strcmp를 넣어도 될 것 같음
    while (find_node) { // Null이면 while 종료
        if (strcmp(find_node->node_data, node_data) == 0) break;
        before_node = find_node;
        find_node = find_node->next_node; // node 만 찾아서 if 절 밖에서 삭제
    }
    // 삭제 node 를 찾지 못함
    if (find_node == NULL) { 
        printf("data not found : %s\n", node_data);
        return;
    }
    // remove - single node
    if (before_node == NULL && find_node->next_node == NULL) {
        memset(find_node->node_data, 0, sizeof(char) * WORD_MAX_SIZE);
        return;
    }
    // remove - head node
    if (before_node == NULL) {
        list->head_node = find_node->next_node;
        deleteNode(find_node);
        return;
    }
    // remove - tail node
    if (find_node->next_node == NULL) {
        list->tail_node = before_node;
        deleteNode(find_node);
        return;
    }
    before_node->next_node = find_node->next_node;
    deleteNode(find_node);
}

void printList(List* list) {
    Node* current_node = list->head_node;
    // while (current_node != list->tail_node) {
    while (current_node) { // node가 null이면 false로 알아서 종료
        printf("%s\n", current_node->node_data);
        current_node = current_node->next_node;
    }
    // printf("%s\n", list->tail_node->node_data); // print tail node - while(current_node)에선 불필요..
}

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("keywords.txt", "rt");
    // FILE* fp = fopen("test.txt", "rt");
    if (fp == NULL) {
        fputs("file open error", stderr);
        exit(1);
    }

    // 리스트 초기화
    List* list = newList();
    Node* node = list->tail_node;
    // while (fscanf(fp, "%s", node->node_data) != EOF) {
    while (!feof(fp)) {
        fscanf(fp, "%s", node->node_data);
        // node = addNode(node, list);
        node = addNode(list);
    }
    printf("==== Before ====\n");
    printList(list); // 출력

    // ZOO 삭제
    removeNode("ZOO", list);
    printf("==== After ====\n");
    printList(list); // 출력

    // free
    deleteList(list);
    fclose(fp);
    return 0;
}
