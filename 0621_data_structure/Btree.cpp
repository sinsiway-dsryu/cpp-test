#include <cstdio>
#include <cstring>
#define MAX 10

struct Node {
    int data;
    Node* left_node;
    Node* right_node;
};

struct Tree {
    Node* root_node;
};

// 이진트리는 항상 root로 값이 들어와야, 대소비교를 하면서 리프 노드를 붙이는 
void insertTree(int number, Node* node) {
    if (node == NULL) {
        node = new Node;
        node->data = number;
        node->left_node = NULL;
        node->right_node = NULL;
        return;
    }
    // 대소비교하고 재귀
    if (node->data >= number) {
        insertTree(number, node->right_node);
    }
    if (node->data < number) {
        insertTree(number, node->left_node);
    }
}

// 이진트리 출력 - 중위순회
void printTree(Node* node) {
    if (node->left_node == NULL) {
        printf("%d\n", node->data);
    }
    if (node->right_node == NULL) {
        printf("%d\n", node->data);
    }

}

int main(int argc, char const *argv[])
{
    // 트리 초기화
    Tree tree;
    tree.root_node = NULL;
    // 숫자 입력 받기
    int number;
    for (int i = 0; i < MAX; i++) {
        printf("insert number : ");
        scanf("%d", &number);

    }
    
    

    return 0;
}
