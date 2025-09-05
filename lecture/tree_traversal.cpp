#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int key;
    Node *parent;
    Node *leftChild;
    Nide *rightSibling;
    int data;
} Node;


void preorder(Node *node) {
    if(node->leftChild != nullptr) {
        preorder(node->leftChild);
    }
    if(node->rightSibling != nullptr) {
        preorder(node->rightSibling);
    }
    
}

void postorder(Node *node) {
    if(node == nullptr) return;
    postorder(node->leftChild);
    postorder(node->rightSibling);
    cout << node->data << " ";
}

void createRoot(int n, Node *node) {

}

int main() {

    Node* node1 = createRoot(1);
    Node* node2 = createNode(2, node1);
    Node* node3 = createNode(3, node1);
    Node* node4 = createNode(4, node2);
    Node* node5 = createNode(5, node1);
    Node* node6 = createNode(6, node1);
    Node* node7 = createNode(7, node3);
    Node* node8 = createNode(8, node7);
    Node* node9 = createNode(9, node7);
    Node* node10 = createNode(10, node3);
    Node* node11 = createNode(11, node3);
    Node* node12 = createNode(12, node11);

    preorder(node1);
    return 0;
}