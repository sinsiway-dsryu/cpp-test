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

Node* newNode(int number) {
    Node* node = new Node;
    node->data = number;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;
} 

// 이진트리는 항상 root로 값이 들어와야, 대소비교를 하면서 리프 노드를 붙이는 
void addNode(Node* node, int number) {
    if (node == NULL) {
        newNode(number);
    }
    // 대소비교하고 재귀
    if (node->data < number) {
        Node* child_node = new Node;
        child_node->data = number;

    }
    if (node->data > number) {
        addNode(number, node->right_node);
    }
}

// 이진트리 출력 - 중위순회
// r -> l -> l -> l -> x -> p -> r -> x -> p
void printNode(Node* child_node, Node* parent_node) {
    if (child_node->left_node == NULL && child_node->right_node == NULL) {
        printf("%d\n", child_node->data);
        if (child_node != parent_node) {
            printRightNode();
        }
    }
    if (child_node->left_node != NULL) {
        printNode(child_node->left_node, child_node);
    } 
    if (child_node->right_node != NULL) {
        printf("%d\n", child_node->data);
        printNode(child_node->right_node, child_node);
    }
     
}

void printRightNode(Node* child_node, Node* parent_node) {
    if (child_node->right_node != NULL) {
        printTree(child_node->right_node, child_node);
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
