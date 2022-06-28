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

}

Node* addNode(Node* before_node, List* list) {
    Node* new_node = newNode();
    before_node->next_node = new_node;
    list->tail_node = new_node;
    return new_node;
}

void removeNode(const char* node_data, List* list) {
    // find
    Node* current_node = list->head_node;
    Node* before_node = NULL;
    int find_flag = 1;
    while (current_node != NULL) {
        if ((find_flag = strcmp(current_node->node_data, node_data)) == 0) break;
        before_node = current_node;
        current_node = current_node->next_node;
    }
    if (find_flag == 1) {
        printf("data not found : %s\n", node_data);
        return;
    }
    // remove
    // remove - single node
    if (before_node == NULL && current_node->next_node == NULL) {
        memset(current_node->node_data, 0, sizeof(char) * WORD_MAX_SIZE);
        return;
    }
    // remove - head node
    if (before_node == NULL) {
        list->head_node = current_node->next_node;
        deleteNode(current_node);
        return;
    }
    // remove - tail node
    if (current_node->next_node == NULL) {
        list->tail_node = before_node;
        deleteNode(current_node);
        return;
    }
    before_node->next_node = current_node->next_node;
    deleteNode(current_node);
}

void printList(List* list) {
    Node* current_node = list->head_node;
    while (current_node->next_node != NULL) {
        printf("%s\n", current_node->node_data);
        current_node = current_node->next_node;
    }
}

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("keywords.txt", "rt");
    if (fp == NULL) {
        fputs("file open error", stderr);
        exit(1);
    }

    // 리스트 초기화
    List* list = newList();
    Node* node = list->tail_node;
    while (fscanf(fp, "%s", node->node_data) != EOF) {
        node = addNode(node, list);
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
