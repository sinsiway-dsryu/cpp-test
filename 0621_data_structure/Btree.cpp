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

// struct NodeStack {
//     int index;
//     Node** node_stack;
//     void push(Node* node) {
//         node_stack[index] = node;
//         if (index < MAX) index++;
//     }
//     Node* pop() {
//         Node* node = node_stack[index];
//         if (index > 0) index--;
//         return node;
//     }
// };

// void printRightNode(Node* node, NodeStack* stack);
// void printLeftNode(Node* node, NodeStack* stack);

// 이진트리는 항상 root로 값이 들어와야, 대소비교를 하면서 리프 노드를 붙이는 
// new를 해서 node를 주소 변수에 넣어줘야 하는건데, 파라미터로 받은 변수에 전달될꺼라 착각
// 전달되게하려면 파라미터를 더블포인터로 받았어야
Node* addNode(int number, Node* node) {
    if (node == NULL) {
        node = new Node;
        node->data = number;
        node->left_node = node->right_node = NULL;
        return node;
    }
    // 대소비교하고 재귀
    if (number < node->data) {
        node->left_node = addNode(number, node->left_node); 
    }
    if (number > node->data) {
        node->right_node = addNode(number, node->right_node);
    }
    return node; // 하위 노드를 붙이고 상위 노드 - 파라미터로 들어온 노드가 리턴됨
}

// 재귀..를 충분히 이해하지 못함
// return;을 걸면 상위 스택으로 올라가면서 다음 라인을 진행할건데
// 
void printNode(Node* node) {
    if (node == NULL) return;
    printNode(node->left_node);
    printf("%d ", node->data);
    printNode(node->right_node);
}

// 이진트리 출력 - 중위순회
// void printRightNode(Node* node, NodeStack* stack) {
//     if (node->right_node != NULL) {
//         printf("%d\n", node->data);
//         printLeftNode(node->right_node, stack);
//     }
//     printf("%d\n", node->data);
//     printLeftNode(stack->pop(), stack);
// }

// void printLeftNode(Node* node, NodeStack* stack) {
//     if (node->left_node != NULL) {
//         stack->push(node);
//         printLeftNode(node->left_node, stack);
//     }
//     printf("%d\n", node->data);
//     printRightNode(stack->pop(), stack);
// }

int main(int argc, char const *argv[])
{
    // 트리 초기화
    Tree tree;
    tree.root_node = NULL;
    // 노드 스택 초기화
    // NodeStack* stack = new NodeStack;
    // stack->index = 0;
    // stack->node_stack = new Node*[MAX];
    // 숫자 입력 받기
    // int number;
    // for (int i = 0; i < MAX; i++) {
    //     printf("insert number : ");
    //     scanf("%d", &number);
    //     addNode(number, tree.root_node);
    // }
    int number[10] = {6,3,1,4,2,5,9,7,10,8};
    for (int i = 0; i < MAX; i++) {
        // addNode(number[i], tree.root_node); // tree.root_node는 처음에 NULL을 파라미터에 준다.
        tree.root_node = addNode(number[i], tree.root_node); // parent를 받아서 다시 입력
        printf("%d ", tree.root_node->data);
    }
    // 중위순회
    // printLeftNode(tree.root_node, stack);
    // printNode(tree.root_node);

    return 0;
}
